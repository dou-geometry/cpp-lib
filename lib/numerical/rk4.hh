#pragma once

#include"../dyn/mono.hh"

// RK4 currently only support 2-order ODE

namespace d::numerical::rk4 {
    const double h=1e-4;
    template<typename C> d::coord<C> run();
    template<typename C> d::dyn::mono<C> next();
}

#include"./rk4.tt"
