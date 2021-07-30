#pragma once
#include"../concepts/coordCarrier.hh"

namespace d {
    template<typename T>
        inline T translate(T x, const d::coord<double>& delta) {
            if constexpr(d::coordCarrier<T>) {
                for(di i=0; i<x.dim; ++i)
                    x.d[i]+=delta;
                return x;
            } else {
                return x+delta;
            }
        };
}
