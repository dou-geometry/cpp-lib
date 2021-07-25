#pragma once
#include"../cls/coord.hh"
#include<concepts>
#include"./coordCarrier"

namespace d {
template<typename T>
requires d::coordCarrier<T>
concept dim2 = requires(const T& x) {
    x[0].dim==2;
}

template<typename T>
requires (!(d::coordCarrier<T>))
concept dim2 = requires(const T& x) {
    x.dim==2;
}
}
