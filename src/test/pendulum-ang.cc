#include"../lib/dou/geo/rk4.hh"
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
    auto a=[](d::coord<double> x) { return d::coord<double>({0, -G/x[0]*std::sin(x[1])}); };
    d::coord<double> d({1, 2}), b({2, 4}), c({2, 0});
    d::dyn::mono<double, true> m(2ul, 0.0, d, b, c);
    std::cout << m << std::endl;
    m.shift<-1>(c);
    std::cout << m << std::endl;
}
