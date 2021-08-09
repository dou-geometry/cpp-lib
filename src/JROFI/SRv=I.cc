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

std::string plot(const d::dyn::mono<double, true>& m, d::conn::sage::settings::files<d::conn::sage::settings::png>& info) {
    std::cout << "Plotting" << std::endl;
    info.scriptf<<"#!/bin/usr/env sage\n";
    info.scriptf<<"import sys\n";
    info.scriptf<<"from sage.all import *\n";
    info.scriptf<<"def parseLines():\n";
    info.scriptf<<"    pts=[]\n";
    info.scriptf<<"    i=0\n";
    info.scriptf<<"    for l in sys.stdin:\n";
    info.scriptf<<"        l=l.rstrip()\n";
    info.scriptf<<"        l=sage_eval(l)\n";
    info.scriptf<<"        pts.append(vector((i*0.01, l)))\n";
    info.scriptf<<"        i+=1\n";
    info.scriptf<<"    return pts\n";
    info.scriptf<<"def main():\n";
    info.scriptf<<"    Gph=points(parseLines())\n";
    info.scriptf<<"    Gph.save(filename=sys.argv[1])\n";
    info.scriptf<<"main()\n";
    for(di i=0; i<m.logSize; ++i) info.dataf << m.log[i][0] << "\n";
    return d::conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}

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
