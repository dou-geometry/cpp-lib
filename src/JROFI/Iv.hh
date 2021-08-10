#pragma once

#include"../../lib/signal/handle.hh"
#include"../../lib/cls/coord.hh"
#include"../../lib/cls/compact/coord.hh"
#include"../../lib/dyn/mono.hh"
#include"../../lib/numerical/rk4.hh"
#include <cmath>
#include<iostream>
#include<string>
#include<atomic>

#define pow23(X) pow(sqrt(X), 3.)

namespace d::Iv {

    static bool low(const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return (1-m[0][0])<1e-2;
    }
    static bool medium(const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return (1-m[0][0])<2e-4;
    }
    static bool high(const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return (1-m[0][0])<2e-5;
    }

}
