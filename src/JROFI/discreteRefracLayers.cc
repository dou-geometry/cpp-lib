#include<iostream>
#include<coord.hh>
#include<oricoord.hh>
#include<func.hh>
#include<orimono.hh>
#include<cassert>
#define DATAAMOUNT 1224
#define singleSideThickness 2.

double refrac(double theta, double vin, double vout) { if(vin==vout) return theta; else return std::asin(std::sin(theta)*vout/vin); }

void calc() {
}

std::pair<d::polarcoord, d::polarcoord> runSnell(d::polarmono& m, const d::numerical::compact::func1d<double, DATAAMOUNT>& v) {
    // init log
    m.karaLog=new d::Karabinerhaken<d::polarmono>(m);
    auto karaLog=m.karaLog;
    auto curVel=v(m[0][1]);
    double dt=1e-4;
    auto prev=m[0];
    //std::cerr << m[0];
    while(m[0][1]>singleSideThickness-.4) {
        // check at interface, update velocity
        auto nowAng=atan(m[0]);
        auto newAng=refrac(nowAng, curVel, v(m[0][1]));
        // move one step
        prev=m[0];
        m[0]+=m[1]*dt;
        // log
        karaLog=(new d::Karabinerhaken<d::polarmono>(m))->insertAfter(karaLog);
        std::cout << m << std::endl;
    }
    return std::make_pair(prev, m[0]);
}

int main() {
    double inboundAngle, inboundVel, outboundVel;
    std::cin >> inboundAngle;

    d::numerical::compact::func1d<double, DATAAMOUNT> v(0, 1e-4);
    d::polarmono m;
    m[0]=d::polarcoord(singleSideThickness, M_PI/2.)+d::polarcoord(.4, M_PI/2.+inboundAngle);
    m[1]=d::polarcoord(singleSideThickness+.4, -M_PI/2.+inboundAngle);
    std::cout << "Init: "<<m<<std::endl;
    auto [prevOut, res]=runSnell(m, v);
    d::compact::line inboundRay(m.karaLog->d[0], m.karaLog->tugi->d[0]),
        outboundRay(res, prevOut);
    std::cout << "Intersecting angle="<<(d::deg)(inboundRay.ang(outboundRay))<<std::endl;
    //assert(res[0]==outboundCheck[0]);
	return 0;
}
