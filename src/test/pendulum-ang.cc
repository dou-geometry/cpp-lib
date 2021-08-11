#include"../../lib/cls/coord.hh"
#include"../../lib/dyn/mono.hh"
#include"../../lib/numerical/rk4.hh"
#include"../../lib/conn/sage/settings.hh"
#include"../../lib/conn/sage/plot.hh"
#include <cmath>
#include<iostream>
#include<string>

#define G 9.80665

/* Pendulum Simulation
 * Angle-verion
 * Parameter: [r, ang]
 */

int main() {
    auto a=[](const d::dyn::mono<double, true>& m) { auto x=m[0]; return d::coord<double>({0, -1*G/x[0]*std::sin(x[1])}); };
    d::coord<double> initPos({2, 125.0/180.0*M_PI});
    d::dyn::mono<double, true> m(2ul, initPos, d::coord<double>(2));
    d::numerical::rk4::run<520, false>(m, a, 4.5);
    std::cout << "Data: " << m.logSize << std::endl;
    std::cout <<std::fixed<<std::setprecision(14);
    d::conn::sage::settings::files<d::conn::sage::settings::gif> anim;
    d::conn::sage::settings::files<d::conn::sage::settings::png> gph("/tmp/plot.png", "/tmp/data");
    //std::cout << d::conn::sage::anime(m, anim);
    std::cout << d::conn::sage::plot(m, gph);
    std::cout << "Animation:\n"<<anim<<"\nPlot:\n"<<gph<<std::endl;
    return 0;
}
