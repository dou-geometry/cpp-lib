#include"../../../lib/cls/coord.hh"
#include"../../../lib/dou/geo/rk4.hh"
#include"../../../lib/manip/translate.hh"
#include <complex>

// User variable

#define inboundDist         2
#define outboundDist        2
#define singleSideThickness 1

#define dTheta 0.00001

#define terminTime 12.24

int main() {
    /* Setup:
     * crossing point: (0, 0)
     * initial position: e^(i*theta), theta\in(pi/2, 3pi/2)
     */
    double theta=M_PI/2.;
    const std::complex<double> i(0,1);
    do {
        theta+=dTheta;
        d::coord<double> initPos(std::exp(i*theta));
        std::cout << "Initial Position: "<<initPos<<std::endl;
        d::dyn::mono<double, true> m((di)2, initPos, initPos*-1);
        d::dou::geo::rk4::run(m, a, terminTime);
    } while(theta<M_PI*1.5);
    return 0;
}
