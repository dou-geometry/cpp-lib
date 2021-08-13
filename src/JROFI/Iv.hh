#pragma once

#include"../../lib/conn/signal/handle.hh"
#include"../../lib/cls/coord.hh"
#include"../../lib/cls/compact/coord.hh"
#include"../../lib/cls/mono.hh"
#include"../../lib/dyn/mono.hh"
#include"../../lib/numerical/rk4.hh"
#include <cmath>
#include<iostream>
#include<string>
#include<atomic>

#define pow23(X) pow(sqrt(X), 3.)

namespace d::IvBackend {

    extern std::atomic<double> tMax;
    std::atomic<double> tMax(0.0);

    static bool belowC(const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return m.t>1.;
    }
    static bool aroundC(const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return m.t>1.2;
    }
    static bool aboveC(const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return m.t>2.4;
    }

    static bool low(const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return (1-m[0][0])<1e-2;
    }
    static bool medium(const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return (1-m[0][0])<2e-4;
    }
    static bool high(const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return (1-m[0][0])<2e-5;
    }

    d::Karabinerhaken<d::dyn::compact::mono<double, 1, 1, true>>* genMoreOnce(bool(*)(const d::dyn::compact::mono<double, 1, 1, true>&)=aroundC, double k=1, double c=1);
    void genMore(bool(*)(const d::dyn::compact::mono<double, 1, 1, true>&)=high, double k=1, double c=1);

    struct funcPoints {
        d::Karabinerhaken<d::dyn::compact::mono<double, 1, 1, true>>* dK=nullptr;
        funcPoints(bool(*cond)(const d::dyn::compact::mono<double, 1, 1, true>&)=belowC, double k=1, double c=1);
    };

    d::Karabinerhaken<d::dyn::compact::mono<double, 1, 1, true>>* const data(bool(*cond)(const d::dyn::compact::mono<double, 1, 1, true>&)=medium, double k=1, double c=1) {
        static funcPoints data(cond, k, c);
        return data.dK;
    }

    //d::dyn::compact::mono<double, 1, 1, true>* shrink(di);

}

namespace d {
    double I(const d::mono<double>&);
    double Iv(double);
}
