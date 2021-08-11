#pragma once
#include"../concepts/returnSame.hh"

namespace d::analysis {
    template<typename T>
        struct batch {
            T* d=nullptr;
            const di dim;
            batch() = delete;
            batch(di d): dim(d) {
                d=new T[dim];
            }
            ~batch() {
                for(di i=0; i<dim; ++i)
                    (d+i)->~T();
                free(d);
            }
            batch(const batch& other): dim(other.dim) {
                d=(T*)malloc(sizeof(T)*dim);
                assert(d!=nullptr);
                for(di i=0; i<dim; ++i)
                    new(d+i)T(other.d[i]);
            }
            T operator[](int i) const {
                return d[i];
            }
            T& operator[](int i) {
                return d[i];
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
            template<typename F> batch requires d::returnSameWithin<F, decltype(*this)> operator()(const F& f) {
                batch res(*this);
                for(di i=0; i<dim; ++i)
                    res[i]=f(res[i]);
                return res;
            }
            }
        };
}
