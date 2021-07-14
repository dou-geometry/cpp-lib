#include"../../include/numerical/rk4.cpp
// Explicit Instantiation
namespace d::numerical::rk4 {
    template coord<float> next();
    template coord<double> next();
    template coord<long double> next();
    template coord<double double> next();
}

// Template Implementation
template<typename C>
coord<C> next() {
}
