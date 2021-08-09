#include"../../lib/signal/handle.hh"
#include"../../lib/cls/coord.hh"
#include"../../lib/dyn/mono.hh"
#include"../../lib/numerical/rk4.hh"
#include"../../lib/conn/sage/settings.hh"
#include"../../lib/conn/sage/plot.hh"
#include <cmath>
#include<iostream>
#include<string>

#define pow23(X) pow(sqrt(X), 3)


int main() {
    signal(SIGTERM, d::signal::handler);
    signal(SIGHUP, d::signal::handler);
    std::cout <<std::fixed<<std::setprecision(14);
    auto dv=[](const d::dyn::mono<double, true>& m) {
        return d::coord<double>({pow(sqrt(1-pow(m[0], 2.)), 3.)});
    };
    d::dyn::mono<double, true> m(1ul, d::coord<double>(1));
    d::obj<double, double> o;
    d::numerical::rk4::run<1, false>(m, dv, 1224);// [&o](d::dyn::mono<double, true> n){ // Insert result into o
    //o.add(n.t, n[0]);
    //});


    // When SIGHUP is issued, the generation of database is terminated and enters lookup
    /*
       double searchKey;
       while(std::cin >> searchKey) {
       std::cout << searchKey << ": " << o(searchKey) << std::endl;
       if(d::signal::SIGTERMcaught) break;
       }
       */
    // SIGTERM to terminate searching loop
    // or use EOF
    //
    for(di i=0; i<m.logSize; ++i) std::cout << m.log[i][0] << std::endl;



    std::cout << "Data: " << m.logSize << std::endl;
    d::conn::sage::settings::files<d::conn::sage::settings::gif> anim;
    d::conn::sage::settings::files<d::conn::sage::settings::png> gph;
    //std::cout << d::conn::sage::anime(m, anim);
    std::cout << plot(m, gph);
    std::cout << "Animation:\n"<<anim<<"\nPlot:\n"<<gph<<std::endl;
    return 0;
}
