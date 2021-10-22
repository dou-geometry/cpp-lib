#pragma once
#include<coordCarrier.hh>
#include<coord.hh>

namespace d {
    template<typename T>
        T translate(T x, const d::coord<double>& delta) {
            if constexpr(d::coordCarrier<T>) {
                for(di i=0; i<x.size(); ++i)
                    d::translate(x.d[i], delta);
                return x;
            } else {
                return x+delta;
            }
        };
}
