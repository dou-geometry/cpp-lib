#include"../../../lib/cls/coord.hh"
#include"../../../lib/cls/line.hh"
#include"../../../lib/numerical/rk4.hh"
#include"../../../lib/manip/translate.hh"
#include"../../../lib/conn/sage/settings.hh"
#include"../../../lib/conn/bash/stdout.hh"
#include <complex>

// User variable

#define inboundDist         2.
#define outboundDist        2.
#define singleSideThickness 1.

#define dTheta 0.1

#define terminTime 12.25

std::string plot(const d::dyn::mono<double, true>& m, d::conn::sage::settings::files<d::conn::sage::settings::png>& info) {
    // Load data
    //if constexpr(d::logIncrPromise && false)
        for(di i=0; i<m.logSize; ++i)
            info.dataf << m.log[i] << std::endl;
    //else
    //    for(di i=0; i<m.logSize; ++i)
    //        info.dataf << "t="<<m.log[i].t<<";" << m.log[i] << std::endl;
    // Load script
    // Execute
    info.dataf.close();
    info.scriptf.close();
    return d::conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}

inline double gaussianFunc(double x) { return std::exp(-1*pow(x,2)); }

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
    do {
        theta+=dTheta;
        theta=M_PI;
        d::coord<double> initPos(std::exp(i*theta)*inboundDist);
        std::cout << "Initial Position: "<<initPos<<std::endl;
        d::dyn::mono<double, true> m((di)2, initPos, initPos*-1);
        std::cout << "Setup: \n"<<m<<std::endl;
        d::numerical::rk4::run<12, false>(m, a, terminTime);
        // Graph path
        d::conn::sage::settings::files<d::conn::sage::settings::png> gph;
        std::cout << "Graphing:\n"<<gph<<std::endl;
        std::cout << plot(m, gph);
        assert(m.logSize>5);
        std::cout << m.log[m.logSize-1] << std::endl;
        d::line<double> inbound(m.log[4][0], m.log[5][0]),
                        outbound(m.log[m.logSize-5][0], m.log[m.logSize-4][0]);
        std::cout << "Intersecting angle: " << d::line<double>::ang(inbound, outbound)/M_PI*180. << std::endl;
        break;
    } while(theta<M_PI*1.5);
    return 0;
}
