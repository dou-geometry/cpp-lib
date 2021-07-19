#include"../lib/numerical/rk4.hh"
#include <cmath>
#include<iostream>

#define G 9.80665

/* Pendulum Simulation
 * Angle-verion
 * Parameter: [r, ang]
 */

int main() {
    auto a=[](d::coord<double> x) { return -G/x[0]*std::sin(x[1]); };
    d::dyn::mono<double, true> m(2);
    m.pos=d::coord<double>({2, 0});
    m=d::numerical::rk4::run(m, a, 10.0);
    std::cout << m << std::endl;
}
