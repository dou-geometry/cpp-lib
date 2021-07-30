#pragma once

namespace d::analysis {
    template<typename T>
        struct batch {
            T* d;
            const di dim;
            batch() = delete;
            batch(di d): dim(d) {
                d=new T[dim];
            }
            ~batch() {
                delete[]d;
            }
            batch(const batch& other): dim(other.dim) {
                d=new T[dim];
                memcpy(d, other.d, sizeof(T)*dim);
            }
            batch& pow(double p) {
                for(di i=0; i<dim; i++)
                    d[i]=std::pow(d[i], p);
                return *this;
            }
            batch pow(double p) const {
                auto res(*this);
                for(di i=0; i<res.dim; i++)
                    res.d[i]=std::pow(res.d[i], p);
                return res;
            }
            template<typename I> I() const {
                I res=0;
                for(di i=0; i<dim; i++)
                    res+=d[i];
                return res;
            }
            double distTo(const batch& target) const {
                auto res=target-(*this);
                return res.pow(2);
            }
            template<typename F>
                requires std::convertible_to<F, std::function<T(T)>>
            inline batch& apply(const F& f) {
                for(di i=0; i<dim; ++i)
                    d[i]=f(d[i]);
                return *this;
            }
        };
}
