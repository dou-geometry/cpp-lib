#pragma once

#include"../cls/coord.hh"
#include"../cls/Karabinerhaken.hh"
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
    template<int logTrigger=1, bool runForever=false, typename R, typename F, typename T>
        requires dynMono<R, F> && std::convertible_to<T, std::function<bool(R)>>
        d::Karabinerhaken<R> run(R& cur, const F &f, const T& t, double h=d::numerical::rk4::h);
    template<int logTrigger=1, bool runForever=false, typename R, typename F, typename T>
        requires dynMono<R, F> && (!(std::convertible_to<T, std::function<bool(R)>>))
        R run(R& cur, const F &f, const T tt=0, double h=d::numerical::rk4::h);
    template<typename C> d::dyn::mono<C> next();
}

#include"./rk4.tt"
