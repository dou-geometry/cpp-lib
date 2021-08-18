#pragma once

#include<handle.hh>
#include<coord.hh>
#include<mono.hh>
#include<mono.hh>
#include<rk4.hh>
#include <cmath>
#include<iostream>
#include<string>
#include<atomic>

#define pow23(X) pow(sqrt(X), 3.)

namespace d::IvBackend {

    extern std::atomic<double> tMax;
    std::atomic<double> tMax(0.0);
    extern std::atomic_flag ongoing;
    std::atomic_flag ongoing;
    extern const double k, c;

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

    d::Karabinerhaken<d::dyn::compact::mono<double, 1, 1, true>>* genMoreOnce(bool(*)(const d::dyn::compact::mono<double, 1, 1, true>&)=aroundC);
    void genMore(bool(*)(const d::dyn::compact::mono<double, 1, 1, true>&)=high);

    struct funcPoints {
        d::Karabinerhaken<d::dyn::compact::mono<double, 1, 1, true>>* dK=nullptr;
        funcPoints(bool(*cond)(const d::dyn::compact::mono<double, 1, 1, true>&)=belowC);
    };

    d::Karabinerhaken<d::dyn::compact::mono<double, 1, 1, true>>* const data(bool(*cond)(const d::dyn::compact::mono<double, 1, 1, true>&)=belowC) {
        static funcPoints data(cond);
        return data.dK;
    }

    //d::dyn::compact::mono<double, 1, 1, true>* shrink(di);

}

namespace d {
    double I(const d::mono<double>&);
    double Iv(double);
    double Iv(double, double);
    double IvSearch(double);
}
