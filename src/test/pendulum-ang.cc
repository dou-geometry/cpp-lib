#include"../lib/numerical/rk4.hh"
#include"../lib/cls/coord.hh"
#include"../lib/dyn/mono.hh"
#include <cmath>
#include<iostream>

#define G 9.80665

/* Pendulum Simulation
 * Angle-verion
 * Parameter: [r, ang]
 */

int main() {
    auto a=[](const d::dyn::mono<double, true>& m) { auto x=m[0]; return d::coord<double>({0, -G/x[0]*std::sin(x[1])}); };
    d::coord<double> initPos({2, 125.0/180.0*M_PI});
    d::dyn::mono<double, true> m(2, initPos, d::coord<double>(2), d::coord<double>(2));
    d::numerical::rk4::run<100, false>(m, a, 1.2);
    std::cout << "Data: " << m.logSize << std::endl;
    for(di i=0; i<m.logSize; ++i)
        std::cout << m.log[i] << std::endl;
}
