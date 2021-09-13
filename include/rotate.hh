#pragma once
#include<coord.hh>
#include<coordCarrier.hh>
#include<dim2.hh>
#include<matrix.hh>

namespace d {
    template<typename T>
        //requires d::dim2<T>
        inline T rotate(T x, double theta) {
            if constexpr(d::coordCarrier<T>) {
                for(di i=0; i<x.size(); ++i)
                    x[i]=d::matrix<double>::R(theta)*x[i];
                return x;
            } else
                return d::matrix<double>::R(theta)*x;
        };
}
