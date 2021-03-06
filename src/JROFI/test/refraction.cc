#include <signal.h>
#include <unistd.h>
#include <cstring>
#include <atomic>

std::atomic<bool> quit(false);    // signal flag

void got_signal(int)
{
    quit.store(true);
}
// Safely handle SIGINT
// By: https://stackoverflow.com/a/4250601/8460574


#include<coord.hh>
#include<line.hh>
#include<rk4.hh>
#include<translate.hh>
#include<settings.hh>
#include<stdout.hh>
#include <complex>
#include <cstdlib>

// User variable

#define inboundDist         4.
//#define outboundDist        2.
//#define singleSideThickness 1.

#define dTheta 1e-4

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
    info.scriptf<<"                if(vct[0]>4.2): break\n";
    info.scriptf<<"                pts.append(vct)\n";
    info.scriptf<<"            cc+=1\n";
    info.scriptf<<"    return pts\n";
    info.scriptf<<"def main():\n";
    info.scriptf<<"    pts=parseFrame()\n";
    info.scriptf<<"    a=(pts[1][1]-pts[0][1])/(pts[1][0]-pts[0][0])\n";
    info.scriptf<<"    b=pts[1][1]-a*pts[1][0]\n";
    info.scriptf<<"    c=(pts[-1][1]-pts[-2][1])/(pts[-1][0]-pts[-2][0])\n";
    info.scriptf<<"    d=pts[-2][1]-c*pts[-2][0]\n";
    info.scriptf<<"    Gph=line(pts, color=\"purple\")+plot(a*x+b, (x,-4,0.12), color=\"red\")+plot(c*x+d, (x, -0.12, 4), color=\"blue\")\n";
    info.scriptf<<"    Gph.save(filename=sys.argv[1], xmin=-4, xmax=4, ymin=-4, ymax=4, aspect_ratio=1, dpi=300)\n";
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
    //return d::conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
    std::cout << std::flush;
    std::system(("sage "+info.script+" "+info.plot+" < "+info.data+" &").c_str());
    return "Sent to background";
}

inline double gaussianFunc(double x) { return std::exp(-1*pow(x,2)); }
//inline double gaussianFunc(double x) { return 1./std::sqrt(2.*M_PI)/singleSideThickness/5./std::sqrt(2*std::log(2))*std::exp(-1.*pow(x,2)/2./std::pow(singleSideThickness/5./std::sqrt(2*std::log(2)), 2)); }

int main(int argc, char** argv) {
    struct sigaction sa;
    memset( &sa, 0, sizeof(sa) );
    sa.sa_handler = got_signal;
    sigfillset(&sa.sa_mask);
    sigaction(SIGINT,&sa,NULL);

    std::cout << std::fixed << std::setprecision(12);
    std::cout << "Inbound,  Outbound, AngB.t.\n";
    /* Setup:
     * crossing point: (0, 0)
     * initial position: e^(i*theta), theta\in(pi/2, 3pi/2)
     */
    double theta=M_PI/2.;
    const std::complex<double> i(0,1);
    double amp=(argc<2?1.:std::atof(argv[1]));
    auto a=[amp](d::dyn::mono<double> m) {
        return d::coord<double>({gaussianFunc(m[0][0]), 0})*(m[1].norm())*amp;
    };
    d::conn::sage::settings::files<d::conn::sage::settings::png> gph(false);
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
        std::cout << (theta-M_PI)/M_PI*-180. << ", " << outbound.ang()/M_PI*180. << ", " << d::line<double>::ang(inbound, outbound)/M_PI*180.<<std::endl;
        if( quit.load() ) break; //Safely handle SIGINT
    } while(theta<M_PI);
    return 0;
}
