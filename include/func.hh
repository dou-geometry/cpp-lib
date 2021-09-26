#pragma once
#include<field.hh>
#include<sets.hh>
#include<functional>
#include<utility>
#include<concepts>
#include<type_traits>
namespace d::numerical {

    static const char hidari  = -1;
    static const char migi    = 1;
    static const char split   = 0;
    static const char exclusive=2;
    static const char inclusive=-2;

template<typename T>
requires std::signed_integral<T> || std::floating_point<T> // As we use unsign/sign coordinates to determine whether or not it's dL or dLinversed;
struct func;

namespace corrfunc {
    template<typename T> T linear(const d::numerical::func<T>&, const d::coord<T>&);
}

template<typename T>
requires std::signed_integral<T> || std::floating_point<T> // As we use unsign/sign coordinates to determine whether or not it's dL or dLinversed;
struct func:field<T> {
    const di dim;
    const coord<T> einPunkt;
    const coord<T> dLi;
    T (*correction)(const coord<T>& crd) = &(corrfunc::linear);
    func(): dim(1), einPunkt(1, (T)0), dLi(1, (T)1) {}
    func(di d): dim(d), einPunkt(d, (T)0), dLi(d, (T)1) {};
    func(coord<di> i): dim(i.dim), einPunkt(i.dim, (T)0), dLi(i) {};
    func(coord<T> d): dim(d.dim), einPunkt(d.dim, (T)0), dLi(d.inv()) {}
    func(coord<T> d, coord<T> eP): dim(d.dim), einPunkt(eP), dLi(d.inv()) {}
    func(coord<di> d, coord<T> eP): dim(d.dim), einPunkt(eP), dLi(d) {}
    func(const std::function<T(d::coord<T>)> &f) {
        for(di i=0; i<field<T>::border; i++) {
            field<T>::d[i]=f(field<T>::IDzuCoord(i));
        }
    }
    template<typename...Ts> requires std::convertible_to<std::common_type_t<Ts...>, di> T& operator[](Ts...) {
        constexpr di n = sizeof...(Ts);
    }
    T& operator[](int i) {
        return (*this)[0];
    };
    T operator[](int i) const {
        return (*this)[0];
    }
    template<typename C> C operator()(coord<C> crd) {
        return crd;
    }
    template<typename C> coord<T> hidari(const coord<C>& crd) const {
        return crd;
    }
    template<typename C> std::pair<coord<T>, coord<T>> neighbour(const coord<C>& crd) {
        return std::make_pair(this->hidari(crd), this->migi(crd));
    }
};

}

namespace d::numerical::compact {
    template<typename T, di size, char evalType=d::numerical::split>
    struct func1d:d::compact::coord<T, size> {
        using d::compact::coord<T, size>::d;
        T base=0;
        T dx;
        func1d(T delta, T b, const std::function<T(T)>& sf): base(b), dx(delta) { this->sampleFrom(sf); }
        func1d(const d::R& boundaries): base(boundaries.von()) {
            if(boundaries.inclusive) dx=boundaries.span()/(size-1);
            else dx = boundaries.span()/(size+1);
            if(!boundaries.inclusive) base+=dx;
        }
        func1d(const std::function<T(T)>& sf, const d::R& boundaries): base(boundaries.von()) {
            if(boundaries.inclusive) dx=boundaries.span()/(size-1);
            else dx = boundaries.span()/(size+1);
            if(!boundaries.inclusive) base+=dx;
            this->sampleFrom(sf);
        }
        func1d(T delta=1, T b=0): base(b), dx(delta) {}
        inline T operator()(double x) const {// no auto adjustment
#ifdef SANITYCHECK
            if (x<base) { std::cerr<<x<<" is lesser than "<<this->base<<std::endl; assert(false && "OOR access to func1d, x="); }
            if(x>=(base+dx*size)) assert(false && "Access over right boundary to func1d");
#endif
            x=(x-base)/dx;
            if constexpr(evalType==0) return d[(int)(x + 0.5 - (x<0))]; // https://stackoverflow.com/a/9695341/8460574
            else if constexpr(evalType==1) return d[(int)std::ceil(x)];
            else if constexpr(evalType==-1) return d[(int)std::floor(x)];
            //else if constexpr(evalType==2) return 
            else if constexpr(evalType==-2) return d[(int)x];
            else return d[(int)x];
        }
        inline T& operator()(T x) {// no auto adjustment
#ifdef SANITYCHECK
            if (x<base || x>=(base+dx*size)) assert(false && "OOR access to func1d");
#endif
            x=(x-base)/dx;
            if constexpr(evalType==0) return d[(int)(x + 0.5 - (x<0))]; // https://stackoverflow.com/a/9695341/8460574
            else if constexpr(evalType==1) return d[(int)std::ceil(x)];
            else if constexpr(evalType==-1) return d[(int)std::floor(x)];
            //else if constexpr(evalType==2) return 
            else if constexpr(evalType==-2) return d[(int)x];
            else return d[(int)x];
        }
        inline double operator()(const d::compact::coord<T, 1>& x) const {
            return this->operator()(x[0]);
        }
        inline T& rel(double x) {
#ifdef SANITYCHECK
            if(x<0 || x>=size) assert(false && "OOR access to func1d from rel()");
#endif
            return this->operator()(base+x);
        }
        inline T rel(double x) const {
#ifdef SANITYCHECK
            if(x<0 || x>=size) assert(false && "OOR access to func1d from rel()");
#endif
            return this->operator()(base+x);
        }
        inline int resolve(double x) const {// no auto adjustment
#ifdef SANITYCHECK
            if (x<base || x>=(base+dx*size)) assert(false && "OOR access to func1d from resolve");
#endif
            x=(x-base)/dx;
            if constexpr(evalType==0) return (int)(x + 0.5 - (x<0)); // https://stackoverflow.com/a/9695341/8460574
            else if constexpr(evalType==1) return (int)std::ceil(x);
            else if constexpr(evalType==-1) return (int)std::floor(x);
            //else if constexpr(evalType==2) return 
            else if constexpr(evalType==-2) return (int)x;
            else return (int)x;
        }
        inline int resolveRel(double x) const { return this->resolve(base+x); }
        template<typename F>
            //requires std::convertible_to<F, std::function<T(T)>>
        inline func1d& sampleFrom(const F& sf) {
            for(di i=0; i<size; ++i)
                d[i]=sf(base+dx*i);
            return *this;
        }
        template<typename F>
            //requires std::convertible_to<F, std::function<T(T)>>
        inline func1d& sampleFrom(const F& sf, const d::R& range) {
            if(range.inclusive)
                for(double i=range.von(); i<=range.zu(); i+=dx)
                    d[this->resolve(i)]=sf(i);
            else
                for(double i=range.von()+dx; i<range.zu(); i+=dx)
                    d[this->resolve(i)]=sf(i);
            return *this;
        }
        func1d& expand(int m, int k, int h) requires(evalType==0) {
#ifdef SANITYCHECK
            assert(m<=k && k<=h); // This could be solved by swapping, but extra branch costs time
            assert(d[k]>=d[h] && d[k]<=d[m] && "not incremental!");
#endif
            int amt=h-m-2;
            int occupied=amt/2;
            for(di i=1; i<=occupied; ++i) {
                d[k+i]=d[k];
                d[k-i]=d[k];
            }
            return *this;
        }
        func1d& expand(double m, double k, double h) { return this->expand(this->resolve(m), this->resolve(k), this->resolve(h)); }
        func1d& expand(double m, double h) { return this->expand(m, (m+h)/2., h); }
        func1d& expandRel(double a, double k, double b) { return this->expand(this->resolveRel(a), this->resolveRel(k), this->resolveRel(b)); }
        func1d& expandRel(double a, double b) { return this->expand(this->resolveRel(a), this->resolveRel(b)); }
        explicit operator d::compact::coord<double, 2>*() {
            d::compact::coord<double, 2>* res=new d::compact::coord<double, 2>[size];
            for(di i=0; i<size; ++i) {
                res[i][0]=base+dx*i;
                res[i][1]=d[i];
            }
            return res;
        }
    };
}

#include"./func.tt"
