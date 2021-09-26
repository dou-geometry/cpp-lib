#include<iostream>
#include<coord.hh>
#include<settings.hh>
#include<stdout.hh>
#include<oricoord.hh>
#include<func.hh>
#include<orimono.hh>
#include<sets.hh>
#include<handle.hh>
#include<cassert>
#define DATAAMOUNT 1224 // Recommended 1224 or 20201224 as those are pre-compiled
#define singleSideThickness 2.

double refrac(double theta, double vin, double vout) { if(vin==vout) return theta; else return std::asin(std::sin(theta)*vout/vin); }

#ifdef SANITYCHECK
void noNegInFunc(const d::numerical::compact::func1d<double, DATAAMOUNT>& f) {
    for(di i=0; i<DATAAMOUNT; ++i)
        assert(f.d[i]>0 && "Function has value less than zero!");
    return;
}
#else
void noNegInFunc(const d::numerical::compact::func1d<double, DATAAMOUNT>& f) { return; }
#endif

std::string plot(const d::numerical::compact::func1d<double, DATAAMOUNT>& f, d::conn::sage::settings::files<d::conn::sage::settings::png>& info) {
    info.scriptf<<"#!/usr/bin/env sage\n";
    info.scriptf<<"import sys\n";
    info.scriptf<<"from sage.all import *\n";
    info.scriptf<<"def main():\n";
    info.scriptf<<"    lnc=-2\n";
    info.scriptf<<"    base=0\n";
    info.scriptf<<"    dx=1\n";
    info.scriptf<<"    Gph=Graphics()\n";
    info.scriptf<<"    for ln in sys.stdin:\n";
    info.scriptf<<"        ln=ln.rstrip()\n";
    info.scriptf<<"        lnc+=1\n";
    info.scriptf<<"        d=sage_eval(ln)\n";
    info.scriptf<<"        if(lnc==-1):\n";
    info.scriptf<<"            base=d[0]\n";
    info.scriptf<<"            dx=d[1]\n";
    info.scriptf<<"            continue\n";
    info.scriptf<<"        Gph+=point((d, lnc*dx+base))\n";
    info.scriptf<<"    Gph.save(filename=sys.argv[1])\n";
    info.scriptf<<"main()\n";
    info.dataf <<std::fixed<<std::setprecision(14);
    info.dataf << f.base << ", " << f.dx << "\n";
    for(di i=0; i<DATAAMOUNT; ++i)
        info.dataf << f.d[i] << "\n";
    info.dataf.close();
    info.scriptf.close();
    return d::conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}


d::numerical::compact::func1d<double, DATAAMOUNT> bezier(const d::R& rangeInit, const double vin, const double vout, const double theta, const d::R& rangeCurve) {
    using crd=d::compact::coord<double, 2>;
    assert(rangeCurve.inside(rangeInit));
    // init data
    d::numerical::compact::func1d<double, DATAAMOUNT> res(rangeInit);
    d::R upper(0+res.dx, rangeInit.zu()), lower(rangeInit.von(), 0-res.dx);
    res.sampleFrom([&theta](double y){return std::tan(theta+M_PI/2.)*y;}, upper);
    res.sampleFrom([&](double y){return std::tan(refrac(theta, vin, vout)-M_PI/2.)*y;}, lower);
    res(0)=0;
    // modify as bezier
    /*
    auto bezierSym=[](const crd& P0, const crd& P2, double t){
        std::cout << P0 << std::endl << P2 << std::endl;
        return std::pow(1-t, 2)*P0+std::pow(t, 2)*P2;
    };
    bezierSym(crd({std::tan(refrac(theta, vin, vout))*rangeCurve.von(), rangeCurve.von()}),
            crd({std::tan(theta)*rangeCurve.zu(), rangeCurve.zu()}),
            0.7);
            */
    auto Bx=[&](double y) {
        double a=std::tan(refrac(theta, vin, vout)-M_PI/2.)*rangeCurve.von(),
               b=rangeCurve.von(),
               c=std::tan(theta+M_PI/2.)*rangeCurve.zu(),
               d=rangeCurve.zu();
        return 1./4.*((std::pow(b, 2.)+std::pow(y, 2.))*(a+c) + 2.*b*(a - c)*y)/std::pow(b, 2.);
    };
    res.sampleFrom(Bx, rangeCurve);
    return res;
}

int main(int argc, char**argv) {
    signal(SIGHUP, d::signal::handler);
    double inboundAngle, inboundVel, outboundVel;
    switch(argc) {
        case 1:
            std::cin >> inboundAngle;
            std::cin >> inboundVel;
            std::cin >> outboundVel;
            break;
        case 2:
            inboundAngle=atof(argv[1]);
            std::cin >> inboundVel;
            std::cin >> outboundVel;
            break;
        case 3:
            inboundAngle=atof(argv[1]);
            inboundVel=atof(argv[2]);
            std::cin >> outboundVel;
            break;
        case 4:
            inboundAngle=atof(argv[1]);
            inboundVel=atof(argv[2]);
            outboundVel=atof(argv[3]);
            break;
    }
    assert(inboundAngle<M_PI/2.);

    d::R range(-singleSideThickness-.5, singleSideThickness+.5);
    auto bres=bezier(range, inboundVel, outboundVel, inboundAngle, d::R(-singleSideThickness-.4, singleSideThickness+.4));
    d::conn::sage::settings::files<d::conn::sage::settings::png> fgph;
    std::cout << "Function v(x): \n"<<fgph<<std::endl;
    std::cout << plot(bres, fgph) << std::endl;
    return 0;
}
