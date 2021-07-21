#include"../lib/dou/geo/rk4.hh"
#include <cmath>
#include<iostream>

#define G 9.80665

/* Pendulum Simulation
 * Angle-verion
 * Parameter: [r, ang]
 */
void test(d::dyn::mono<double, true> a) {
    return;
}

int main() {
    auto a=[](d::coord<double> x) { return d::coord<double>({0, -G/x[0]*std::sin(x[1])}); };
    d::coord<double> d({1, 2}), b({2, 4}), c({2, 0});
    d::dyn::mono<double, true> m(2, d, b, c);
    test(m);
    std::cout << ":::" << std::endl;
    std::cout << m.order << std::endl;
    std::cout << m[0] << std::endl;
}
