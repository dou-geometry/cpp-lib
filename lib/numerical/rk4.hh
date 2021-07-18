#pragma once

#include"../cls/coord.hh"
#include"../dyn/mono.hh"
#include<functional>

// RK4 currently only support 2-order ODE

namespace d::numerical::rk4 {
    const double h=1e-4;
    template<bool runForever=false, typename C, typename R, typename F>
        requires std::convertible_to<R, d::coord<C>> && std::convertible_to<F, std::function<d::coord<C>(d::coord<C>)>>
        R run(R cur, const F &f, const double tt=0);
    template<typename C> d::dyn::mono<C> next();
}

#include"./rk4.tt"
