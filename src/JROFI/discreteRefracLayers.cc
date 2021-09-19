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

d::compact::coord<double, 2> runSnell(d::polarmono& m, const d::numerical::compact::func1d<double, DATAAMOUNT>& v) {
    std::cout << "Enter\n";
    // init log
    m.karaLog=new d::Karabinerhaken<d::polarmono>(m);
    auto karaLog=m.karaLog;
    auto curVel=v(m[0][1]);
    double dt=1e-4;
    //std::cerr << m[0];
    return m.posi();
    while(m[0][1]>singleSideThickness-.4) {
        // check at interface, update velocity
        auto nowAng=atan(m[0]);
        auto newAng=refrac(nowAng, curVel, v(m[0][1]));
        // move one step
        m[0]+=m[1]*dt;
        // log
        karaLog=d::Karabinerhaken<d::polarmono>(m).insertAfter(karaLog);
        std::cout << m << std::endl;
    }
    return m.posi();
}

int main() {
    double inboundAngle, inboundVel, outboundVel;
    std::cin >> inboundAngle;

    d::numerical::compact::func1d<double, DATAAMOUNT> v(0, 1e-4);
    d::compact::coord<double, 2> inbound, outboundCheck;
    d::polarmono m(d::polarcoord({1, 2}), d::polarcoord({2, 4}));
    //std::cout << m[0] << std::endl;
    inbound.polar(singleSideThickness+2.4, inboundAngle, true);
    outboundCheck.polar(singleSideThickness+2.4, refrac(inboundAngle, inboundVel, outboundVel)+M_PI, true);
    std::cout << "Ready\n";
    auto res=runSnell(m, v);
    //std::cout << "Log start: "<<m.karaLog << std::endl;
    //for(auto ptr=m.karaLog; ptr!=nullptr; ptr=ptr->tugi) std::cout << ptr << std::endl;
    //assert(res[0]==outboundCheck[0]);
	return 0;
}
