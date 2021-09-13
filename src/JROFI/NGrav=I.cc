#include<iostream>
#include<coord.hh>
#include<mono.hh>
#include<rk4.hh>
#include<IgN.hh>
#include<settings.hh>
#include<plot.hh>

#define mn d::dyn::compact::mono<double, 2ul, (di)1, true>
#define zh d::compact::coord<double, (di)1>

std::string plot(auto& m, d::conn::sage::settings::files<d::conn::sage::settings::png>& info) {
info.scriptf<<"#!/usr/bin/env sage\n";
info.scriptf<<"import sys\n";
info.scriptf<<"from sage.all import *\n";
info.scriptf<<"def parseLine():\n";
info.scriptf<<"    pts=[]\n";
info.scriptf<<"    for ln in sys.stdin:\n";
info.scriptf<<"        pts.append(vector(sage_eval(ln.rstrip())))\n";
info.scriptf<<"    return pts\n";
info.scriptf<<"def main():\n";
info.scriptf<<"    Gph=line(parseLine())\n";
info.scriptf<<"    fnN=sys.argv[1]\n";
info.scriptf<<"    Gph.save(fnN,dpi=1224)\n";
info.scriptf<<"main()\n";
    info.dataf <<std::fixed<<std::setprecision(14);
    for(di i=0; i<m.logSize; ++i)
        info.dataf<<"("<<m.log[i].t<<", "<<m.log[i][0][0]<<")\n";
    info.dataf.close();
    info.scriptf.close();
    return d::conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}

int main(int argc, char** argv) {
    double x0, v0, tt;
    std::cout << "Initial Position=";
    std::cin >> x0;
    std::cout << "Initial Velocity=";
    std::cin >> v0;
    std::cout << "Terminal Time=";
    std::cin >> tt;
    mn m(0.0, zh({x0}), zh({v0}));
    //const double vr=v0/d::Ig(x0);
    auto dx=[](const mn& m) {
        //std::cout <<vr*d::Ig(m[0][0])  << std::endl;
        //return zh({vr*d::Ig(m[0][0])});
        const zh dx({1e-12}); //must be positive
        auto migi=(m[0]+dx), hidari=(m[0]-dx);
        double dir=d::Ig(migi.norm())>d::Ig(hidari.norm())?1.:-1.;
        auto res=zh({(d::Ig(migi.norm())-d::Ig(hidari.norm()))/(2*dx.norm())});
        /*
        std::cout << m[0] << std::endl;
        std::cout << dir << std::endl;
        std::cout << res << std::endl;
        std::cout << std::endl;
        */
        return res;
    };
    d::numerical::rk4::run<1224, false>(m, dx, tt);
    std::cout << m << std::endl;
    //std::cout << (argv[1][0]=='n')<< std::endl;
    if(argc>1 && argv[1][0]=='n') return 0;
    d::conn::sage::settings::files<d::conn::sage::settings::png> gph;
    std::cout << gph << std::endl;
    std::cout << plot(m, gph) << std::endl;
    //std::cin >> a;
    return 0;
}
