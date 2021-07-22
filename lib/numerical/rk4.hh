#pragma once

#include"../cls/coord.hh"
#include"../dyn/mono.hh"
#include"../concepts/tracksTime.hh"
#include<functional>

// RK4 currently only support 2-order ODE

namespace d::numerical::rk4 {
    const double h=1e-4;
    template<typename R, typename F>
        concept dynMono = requires(const R &r, const F &f) {
            std::convertible_to<F, std::function<typename std::decay<decltype(r[0])>::type(R)>>;
            {f(r)}->std::same_as<typename std::decay<decltype(r[0])>::type>;
            std::convertible_to<R, typename std::decay<decltype(r[0])>::type>;
        };
    template<bool runForever=false, typename R, typename F>
        requires dynMono<R, F>
        R run(R& cur, const F &f, const double tt=0);
    template<typename C> d::dyn::mono<C> next();
}

#include"./rk4.tt"
