#pragma once
#include<field.hh>
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
        func1d(T d, T b, const std::function<T(T)>& sf): base(b), dx(d) { this->sampleFrom(sf); }
        func1d(T d=1, T b=0): base(b), dx(d) {}
        inline T operator()(T x) const {// no auto adjustment
            if constexpr(evalType==0) return d[(int)(x + 0.5 - (x<0))]; // https://stackoverflow.com/a/9695341/8460574
            else if constexpr(evalType==1) return d[(int)std::ceil(x)];
            else if constexpr(evalType==-1) return d[(int)std::floor(x)];
            //else if constexpr(evalType==2) return 
            else if constexpr(evalType==-2) return d[(int)x];
            else return d[(int)x];
        }
        inline T& operator()(T x) {// no auto adjustment
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
        template<typename F>
            requires std::convertible_to<F, std::function<T(T)>>
        inline func1d& sampleFrom(const F& sf) {
            for(di i=0; i<size; ++i)
                d[i]=sf(base+dx*i);
            return *this;
        }
    };
}

#include"./func.tt"
