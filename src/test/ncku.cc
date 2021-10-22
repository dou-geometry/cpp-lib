#include<coord.hh>
#include<mono.hh>
#include<rk4.hh>
#include<plot.hh>
#include <cmath>
#include<iostream>
#include<string>

#define G 9.80665

/* Pendulum Simulation
 * Angle-verion
 * Parameter: [r, ang]
 */

int main() {
    std::cout <<std::fixed<<std::setprecision(14);
    auto a=[](const d::dyn::mono<double, true>& m) { return d::coord<double>({-2*m[2][0]-m[0][0]}); };
    d::coord<double> initPos({2.});
    d::dyn::mono<double, true> m(4ul, 0.0, d::coord<double>(1), d::coord<double>(1), initPos, d::coord<double>(1));
    d::numerical::rk4::run<0, false>(m, a, 10., 0.01);
    std::cout << "End t="<<m.t<<std::endl;
    std::cout << "Compare: "<<m.t*std::sin(m.t)<<std::endl;
    //std::cout << "Data: " << m.logSize << std::endl;
    d::conn::sage::settings::files<d::conn::sage::settings::gif> anim;
    d::conn::sage::settings::files<d::conn::sage::settings::png> gph("/tmp/plot.png", "/tmp/data");
    //std::cout << d::conn::sage::anime(m, anim);
    //std::cout << d::conn::sage::plot(m, gph);
    //std::cout << "Animation:\n"<<anim<<"\nPlot:\n"<<gph<<std::endl;
    return 0;
}
