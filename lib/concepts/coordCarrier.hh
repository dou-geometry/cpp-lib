#pragma once
#include"../cls/coord.hh"
#include<concepts>

namespace d {
template<typename T>
concept coordCarrier = requires(const T& x) {
    {x[0]}->std::same_as<d::coord<double>>;
};
}
