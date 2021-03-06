#pragma once

#include<coord.hh>
#include<mono.hh>
#include<functional>

// RK4 currently only support 2-order ODE

namespace d::dou::geo::rk4 {
    const double h=1e-4;
    template<typename R>
        concept tracksTime = requires(const R &r) { r.t; };
    template<typename R, typename F>
        concept dynMono = requires(const R &r, const F &f) {
            std::convertible_to<F, std::function<typename std::decay<decltype(r)>::type(typename std::decay<decltype(r)>::type)>>;
            {f(r)}->std::same_as<typename std::decay<decltype(r)>::type>;
            std::convertible_to<R, typename std::decay<decltype(r[0])>::type>;
        };
    template<typename R, typename F>
        concept nurCoord = requires(const R &r, const F &f) {
            std::convertible_to<F, std::function<typename std::decay<decltype(r)>::type(typename std::decay<decltype(r)>::type)>>;
            {f(r)}->std::same_as<typename std::decay<decltype(r)>::type>;
            std::convertible_to<R, typename std::decay<decltype(r)>::type>;
        };
    template<typename R, typename F>
        concept x = (dynMono<R, F> || nurCoord<R, F>);
    template<bool runForever=false, typename R, typename F>
        requires x<R, F>
        R run(R& cur, const F &f, const double tt=0);
    template<typename C> d::dyn::mono<C> next();
}

#include"./rk4.tt"
