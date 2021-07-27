#include"../../../lib/cls/coord.hh"
#include"../../../lib/cls/line.hh"
#include"../../../lib/numerical/rk4.hh"
#include"../../../lib/manip/translate.hh"
#include"../../../lib/conn/sage/settings.hh"
#include"../../../lib/conn/bash/stdout.hh"
#include <complex>

// User variable

#define inboundDist         4.
//#define outboundDist        2.
//#define singleSideThickness 1.

#define dTheta 1e-2

#define terminTime 12.25

void plotScript(d::conn::sage::settings::files<d::conn::sage::settings::png>& info) {
    // Load script
    info.scriptf<<"#!/usr/bin/env sage\n";
    info.scriptf<<"import sys\n";
    info.scriptf<<"from sage.all import *\n";
    info.scriptf<<"def parseFrame():\n";
    info.scriptf<<"    cc=0\n";
    info.scriptf<<"    inFrame=False\n";
    info.scriptf<<"    pts=[]\n";
    info.scriptf<<"    vct=vector((0,0))\n";
    info.scriptf<<"    for ln in sys.stdin:\n";
    info.scriptf<<"        ln=ln.rstrip()\n";
    info.scriptf<<"        if(ln==\"============\"):\n";
    info.scriptf<<"            if(inFrame):\n";
    info.scriptf<<"                inFrame=False\n";
    info.scriptf<<"            else:\n";
    info.scriptf<<"                inFrame=True\n";
    info.scriptf<<"                cc=0\n";
    info.scriptf<<"        else:\n";
    info.scriptf<<"            if(cc==0):\n";
    info.scriptf<<"                vct=vector(sage_eval(ln))\n";
    info.scriptf<<"                pts.append(vct)\n";
    info.scriptf<<"            cc+=1\n";
    info.scriptf<<"    return pts\n";
    info.scriptf<<"def main():\n";
    info.scriptf<<"    Gph=line(parseFrame())\n";
    info.scriptf<<"    Gph.save(filename=sys.argv[1], xmin=-2, xmax=2, ymin=-2, ymax=2, aspect_ratio=1)\n";
    info.scriptf<<"main()\n";
    info.scriptf.close();
}

std::string plot(const d::dyn::mono<double, true>& m, d::conn::sage::settings::files<d::conn::sage::settings::png>& info) {
    // Load data
    info.newplot();
    info.newdata();
    for(di i=0; i<m.logSize; ++i)
        info.dataf << m.log[i] << std::endl;
    info.dataf.close();
    // Execute
    return d::conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}

inline double gaussianFunc(double x) { return std::exp(-1*pow(x,2)); }
//inline double gaussianFunc(double x) { return 1./std::sqrt(2.*M_PI)/singleSideThickness/5./std::sqrt(2*std::log(2))*std::exp(-1.*pow(x,2)/2./std::pow(singleSideThickness/5./std::sqrt(2*std::log(2)), 2)); }

int main() {
    std::cout << std::fixed << std::setprecision(12);
    /* Setup:
     * crossing point: (0, 0)
     * initial position: e^(i*theta), theta\in(pi/2, 3pi/2)
     */
    double theta=M_PI/2.;
    const std::complex<double> i(0,1);
    auto a=[](d::dyn::mono<double> m) {
        return d::coord<double>({gaussianFunc(m[0][0]), 0})*(m[1].norm());
    };
    std::vector<double> angles;
    d::conn::sage::settings::files<d::conn::sage::settings::png> gph;
    d::conn::bash::exec("rm "+gph.plot);
    plotScript(gph);
    int ranTime=0;
    do {
        ++ranTime;
        theta+=dTheta;
        d::coord<double> initPos(std::exp(i*theta)*inboundDist);
        d::dyn::mono<double, true> m((di)2, initPos, initPos*-1);
        d::numerical::rk4::run<12, false>(m, a, terminTime);
        // Graph path
        if(ranTime%1224==0) plot(m, gph);
        assert(m.logSize>5);
        d::line<double> inbound(m.log[4][0], m.log[5][0]),
            outbound(m.log[m.logSize-5][0], m.log[m.logSize-4][0]);
        std::cout << d::line<double>::ang(inbound, outbound)/M_PI*180.<<std::endl;
    } while(theta<M_PI);
    for(auto &i:angles)
        std::cout << i << std::endl;
    return 0;
}
