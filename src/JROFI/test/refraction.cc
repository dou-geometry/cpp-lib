#include"../../../lib/cls/coord.hh"
#include"../../../lib/numerical/rk4.hh"
#include"../../../lib/manip/translate.hh"
#include"../../../lib/conn/sage/settings.hh"
#include <complex>

// User variable

#define inboundDist         2.
#define outboundDist        2.
#define singleSideThickness 1.

#define dTheta 0.1

#define terminTime 12.24

std::string plot(const d::dyn::mono<double, true>& m, const d::conn::sage::settings::files<d::conn::sage::settings::png>& info) {
    // Load data
    if constexpr(logIncrPromise && false)
        for(di i=0; i<m.logSize; ++i)
            info.dataf << m.log[i] << std::endl;
    else
        for(di i=0; i<m.logSize; ++i)
            info.dataf << "t="<<m.log[i].t<<";" << m.log[i] << std::endl;
    // Load script
    // Execute
    info.dataf.close();
    info.scriptf.close();
    return conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}

int main() {
    std::cout << std::fixed << std::setprecision(12);
    /* Setup:
     * crossing point: (0, 0)
     * initial position: e^(i*theta), theta\in(pi/2, 3pi/2)
     */
    double theta=M_PI/2.;
    const std::complex<double> i(0,1);
    do {
        theta+=dTheta;
        d::coord<double> initPos(std::exp(i*theta)*inboundDist);
        std::cout << "Initial Position: "<<initPos<<std::endl;
        d::dyn::mono<double, true> m((di)2, initPos, initPos*-1);
        std::cout << "Setup: \n"<<m<<std::endl;
        d::numerical::rk4::run(m, a, terminTime);
        // Graph path
        d::conn::sage::settings::files<d::conn::sage::settings::png> gph;
        std::cout << "Graphing:\n"<<gph<<std::endl;
        std::cout << plot(m, gph);
    } while(theta<M_PI*1.5);
    return 0;
}
