#pragma once
#include"../../cls/coord.hh"

namespace d {
    template<typename T>
        requires d::coordCarrier<T>
        T translate(T x, const d::coord<double>& delta) {
            for(di i=0; i<x.dim; ++i)
                d::translate(x.d[i], delta);
            return x;
        };
    template<typename T>
        requires (!(d::coordCarrier<T>))
        inline T translate(T x, const d::coord<double>& delta) {
            return x+delta;
        };
}
