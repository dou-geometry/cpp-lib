#pragma once
#include"../cls/field.hh"
#include<functional>
#include<utility>
#include<concepts>
#include<type_traits>
namespace d::numerical {

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

#include"./func.tt"
