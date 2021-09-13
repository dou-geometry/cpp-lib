#pragma once
#include<coord.hh>
#include<concepts>
#include<coordCarrier.hh>

namespace d {
template<typename T>
concept dim2 = requires(const T& x) {
    //((!(d::coordCarrier<T>)) && x.dim==2) || (d::coordCarrier<T> && x[0].dim==2);
    //d::coordCarrier<T>?x[0].dim==2:x.dim==2;
    x.dim==2; //weak
};
}
