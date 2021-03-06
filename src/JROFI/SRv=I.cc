#include"./IvSR.hh"
#include<settings.hh>
#include<plot.hh>

std::string plot(auto* m, d::conn::sage::settings::files<d::conn::sage::settings::png>& info) {
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
    info.scriptf<<"        pts.append(vector((i*1e-4, l)))\n";
    info.scriptf<<"        if i==0: pts=[]\n";
    info.scriptf<<"        i+=1\n";
    info.scriptf<<"    return pts\n";
    info.scriptf<<"def main():\n";
    info.scriptf<<"    Gph=points(parseLines())\n";
    info.scriptf<<"    Gph.save(filename=sys.argv[1], ymin=0, ymax=1)\n";
    info.scriptf<<"main()\n";
    info.dataf <<std::fixed<<std::setprecision(14);
    for(; m!=nullptr; m=m->tugi) info.dataf << m->d.d[0] << "\n";
    //for(di i=0; i<m.logSize; ++i) info.dataf << m.log[i][0] << "\n";
    info.scriptf.close();
    info.dataf.close();
    return d::conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}

const double d::IvBackend::k=1., d::IvBackend::c=1.;
int main() {
    signal(SIGTERM, d::signal::handler);
    signal(SIGHUP, d::signal::handler);
    std::cout <<std::fixed<<std::setprecision(14);
    //auto lg=d::IvBackend::data(d::IvBackend::aboveC, 2, 2);
    //auto lg=d::IvBackend::data(d::IvBackend::aboveC, 1.2, 2.4);
    //auto lg=d::IvBackend::data(d::IvBackend::aboveC);
    std::cout << "Search:\n"<<d::IvSearch(d::Iv(0.2)*d::Iv(0.4)) << std::endl;
    return 0;
    //auto lg=d::IvBackend::data();
    //for(; lg->tugi!=nullptr; lg=lg->tugi) std::cout <<lg->d.t << ", " << lg->d.d[0] << "\n";
    //std::cout <<lg->d.t << ", " << lg->d.d[0] << "\n";
    //d::IvBackend::genMoreOnce(d::IvBackend::medium);
    //std::cout << "genmore"<<std::endl;
    //for(lg=lg->tugi; lg!=nullptr; lg=lg->tugi) std::cout <<lg->d.t << ", " << lg->d.d[0] << "\n";


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
    //for(di i=0; i<m.logSize; ++i) std::cout << m.log[i][0] << std::endl;

    goto plot;

    double k;
    while(std::cin>>k) {
        std::cout << d::Iv(k) << std::endl;
    }
    return 0;

plot:

    std::cout << "Data: " << d::IvBackend::data()->size() << std::endl;
    d::conn::sage::settings::files<d::conn::sage::settings::gif> anim;
    d::conn::sage::settings::files<d::conn::sage::settings::png> gph;
    //std::cout << d::conn::sage::anime(m, anim);
    std::cout << plot(d::IvBackend::data(), gph);
    std::cout << "Animation:\n"<<anim<<"\nPlot:\n"<<gph<<std::endl;
    std::cout << d::Iv(0.12) << std::endl << d::Iv(0.24) << std::endl;
    return 0;
}
