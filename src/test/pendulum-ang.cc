#include"../lib/numerical/rk4.hh"
#include"../lib/cls/coord.hh"
#include"../lib/dyn/mono.hh"
#include"../lib/conn/sage/settings.hh"
#include"../lib/conn/sage/plot.hh"
#include <cmath>
#include<iostream>
#include<string>

#define G 9.80665

/* Pendulum Simulation
 * Angle-verion
 * Parameter: [r, ang]
 */

int main() {
    auto a=[](const d::dyn::mono<double, true>& m) { auto x=m[0]; return d::coord<double>({0, -G/x[0]*std::sin(x[1])}); };
    d::coord<double> initPos({2, 125.0/180.0*M_PI});
    d::dyn::mono<double, true> m(2, initPos, d::coord<double>(2), d::coord<double>(2));
    d::numerical::rk4::run<10, false>(m, a, 1.2);
    std::cout << "Data: " << m.logSize << std::endl;
    d::conn::sage::settings::files<"gif"> sett("/tmp/animate.gif");
    std::cout << sett << std::endl;
    std::cout << d::conn::sage::anime(m, sett);
    return 0;
}
