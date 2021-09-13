#pragma once

#include<handle.hh>
#include<coord.hh>
#include<Karabinerhaken.hh>
#include<object.hh>
#include<mono.hh>
#include<tracksTime.hh>
#include<functional>

// RK4 currently only support 2-order ODE

namespace d::numerical::rk4 {
    const double h=1e-4;
    template<typename X> static void logRes(X);
    template<typename R, typename F>
        concept dynMono = requires(const R &r, const F &f) {
            std::convertible_to<F, std::function<typename std::decay<decltype(r[0])>::type(R)>>;
            {f(r)}->std::same_as<typename std::decay<decltype(r[0])>::type>;
            std::convertible_to<R, typename std::decay<decltype(r[0])>::type>;
        };
    template<int logTrigger=1, bool runForever=false, typename R, typename F, typename T, typename C=std::function<void(R)>>
        requires dynMono<R, F> && std::convertible_to<T, std::function<bool(R)>> && std::convertible_to<C, std::function<void(R)>>
        d::Karabinerhaken<R>* run(R& cur, const F &f, const T& t, double h=d::numerical::rk4::h, C cb=d::numerical::rk4::logRes<R>);
    template<int logTrigger=1, bool runForever=false, typename R, typename F, typename T, typename C=std::function<void(R)>>
        requires dynMono<R, F> && (!(std::convertible_to<T, std::function<bool(R)>>)) && std::convertible_to<C, std::function<void(R)>>
        R run(R& cur, const F &f, const T tt=0, double h=d::numerical::rk4::h, C cb=d::numerical::rk4::logRes<R>);
    template<typename C> d::dyn::mono<C> next();
}

#include"./rk4.tt"
