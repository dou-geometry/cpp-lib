#include<coord.hh>
#include<oricoord.hh>
#include<func.hh>
#include<mono.hh>
#include<cassert>
#define DATAAMOUNT 1224
#define singleSideThickness 2.
#define dt 1e-4

double refrac(double theta, double vin, double vout) { return std::asin(std::sin(theta)*vout/vin); }

void calc() {
}

/*
d::compact::coord<double, 2> run(double theta, const d::compact::field1d& v) {
    for(di i=0; i<v.size; ++i)
        theta=refrac(theta, v[i], v[i+1]);
    return theta;
}
*/

d::compact::coord<double, 2> run(d::compact::mono<double, 2>& m, const d::compact::func1d& v) {
    // init log
    new(m.karaLog)d::Karabinerhaken<d::compact::mono<T, dimension, logStatus>>(m);
    while(m[0][1]>singleSideThickness-.4) {
        // check at interface, update velocity
        // move one step
        m[0]+=m[1]*dt;
        // log
        m.karaLog=d::Karabinerhaken<d::compact::mono<T, dimension, logStatus>>(m).insertAfter(m.karaLog);
    }
    return m.posi();
}

int main() {
    double inboundAngle, inboundVel, outboundVel;
    std::cin >> inboundAngle;

    d::compact::field1d<double, DATAAMOUNT> v;
    d::compact::coord<double, 2> inbound, outboundCheck;
    inbound.polar(singleSideThickness+2.4, inboundAngle, true);
    outboundCheck.polar(singleSideThickness+2.4, refrac(inboundAngle, inboundVel, outboundVel)+M_PI, true);
    assert(run()==outboundCheck);
	return 0;
}
