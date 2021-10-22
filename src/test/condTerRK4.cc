#include<coord.hh>
#include<mono.hh>
#include<rk4.hh>
#include<plot.hh>
#include <cmath>
#include<iostream>
#include<string>

#define G 9.80665

int main() {
    auto a=[](const d::dyn::mono<double, true>& m) { auto x=m[0]; return d::coord<double>({0, -1*G/x[0]*std::sin(x[1])}); };
    auto cond=[](const d::dyn::mono<double, true>& m) {
        return m[0][1]<0;
    };
    d::coord<double> initPos({2, 125.0/180.0*M_PI});
    d::dyn::mono<double, true> m(2ul, initPos, d::coord<double>(2));
    d::Karabinerhaken<d::dyn::mono<double, true>> *log;
    log=d::numerical::rk4::run(m, a, cond);
    std::cout <<std::fixed<<std::setprecision(14);
    std::cout << log << std::endl;
    return 0;
}
