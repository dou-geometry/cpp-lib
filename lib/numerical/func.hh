#pragma once
#include"../cls/field.hpp"
#include<utility>
#include<concept>
namespace d::numerical {

namespace corrfunc {
    template<typename T> T linear(const func<T>&, const coord<T>&);
}

template<typename T>
require std::signed_integral<T> // As we use unsign/sign coordinates to determine whether or not it's dL or dLinversed;
struct func:field<T> {
    const di dim;
    const coord<T> einPunkt;
    const coord<T> dLi;
    T (*correction)(const coord<T>& crd) const = &(corrfunc::linear);
    func(): dim(1), einPunkt(1, (T)0), dLi(1, (T)1) {}
    func(di d): dim(d), einPunkt(d, (T)0), dLi(d, (T)1) {};
    func(coord<di> i): dim(i.dim), einPunkt(d.dim, (T)0), dLi(i) {};
    func(coord<T> d): dim(d.dim), einPunkt(d.dim, (T)0), dLi(d.inv()) {}
    func(coord<T> d, coord<T> eP): dim(d.dim), einPunkt(eP), dLi(d.inv()) {}
    func(coord<di> d, coord<T> eP): dim(d.dim), einPunkt(eP), dLi(d) {}
    func(const std::function<T(d::coord<T>)> &f) {
        for(di i=0; i<field<T>::border; i++) {
            field<T>::d[i]=f(field<T>::IDzuCoord(i));
        }
    }
    template<typename...Ts> requires convertible_to<Ts, di> T& operator[](Ts...) {
        constexpr di n = sizeof...(T);
    }
    T& operator[](int i) {
    };
    T operator[](int i) const {
    }
    template<typename C> C operator()(coord<C>) {
    }
    template<typename C> coord<T> hidari(const coord<C>& crd) {
    }
    template<typename C> std::pair<coord<T>, coord<T>> neighbour(const coord<C>& crd) {
        return std::make_pair(this->hidari(crd), this->migi(crd));
    }
};

}

#include"./func.tt"
