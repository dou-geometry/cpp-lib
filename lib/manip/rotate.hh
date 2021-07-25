#pragma once
#include"../../concepts/coordCarrier.hh"
#include"../../concepts/dim2.hh"
#include"../../cls/matrix.hh"

namespace d {
    template<typename T>
        requires d::coordCarrier<T> && d::dim2<T>
        T rotate(T x, double theta) {
            for(di i=0; i<x.dim; ++i)
                d::rotate(x.d[i], theta);
            return x;
        };
    template<typename T>
        requires (!(d::coordCarrier<T>)) && d::dim2<T>
        inline T rotate(T x, double theta) {
            return d::matrix::R(theta)*x;
        };
}
