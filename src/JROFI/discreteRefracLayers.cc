#include<iostream>
#include<coord.hh>
#include<settings.hh>
#include<stdout.hh>
#include<oricoord.hh>
#include<func.hh>
#include<orimono.hh>
#include<sets.hh>
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

//double stdNormDist(double x) { return 1/std::sqrt(2.*M_PI)*std::exp(x*x/-2.); }

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
    info.scriptf<<"        Gph+=point((lnc*dx+base, d))\n";
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

std::string plot(const d::polarmono& m, d::conn::sage::settings::files<d::conn::sage::settings::png>& info) {
    info.scriptf<<"#!/usr/bin/env sage\n";
    info.scriptf<<"import sys\n";
    info.scriptf<<"from sage.all import *\n";
    info.scriptf<<"def main():\n";
    info.scriptf<<"    E.<x,y> = EuclideanSpace(2)\n";
    info.scriptf<<"    cartesian = E.cartesian_coordinates()\n";
    info.scriptf<<"    polar.<r,t> = E.polar_coordinates()\n";
    info.scriptf<<"    pts=[]\n";
    info.scriptf<<"    for ln in sys.stdin:\n";
    info.scriptf<<"        ln=ln.rstrip()\n";
    info.scriptf<<"        d=ln.split(\"=\")\n";
    info.scriptf<<"        x=sage_eval(d[1][:-3])\n";
    info.scriptf<<"        [curX, curY]=E.coord_change(polar, cartesian)(x[0], x[1])\n";
    info.scriptf<<"        pts.append((curX, curY))\n";
    info.scriptf<<"    ms=(pts[1][1]-pts[0][1])/(pts[1][0]-pts[0][0])\n";
    info.scriptf<<"    bs=pts[1][1]-ms*pts[1][0]\n";
    info.scriptf<<"    me=(pts[-2][1]-pts[-1][1])/(pts[-2][0]-pts[-1][0])\n";
    info.scriptf<<"    be=pts[-1][1]-me*pts[-1][0]\n";
    info.scriptf<<"    x=var(\"x\")\n";
    info.scriptf<<"    Gph=line(pts)+plot(ms*x+bs, (x, pts[0][0], pts[-1][0]), color=\"red\", alpha=0.4)+plot(me*x+be, (x, pts[0][0], pts[-1][0]), color=\"violet\", alpha=0.4)\n";
    info.scriptf<<"    Gph.save(filename=sys.argv[1])\n";
    info.scriptf<<"main()\n";
    info.dataf <<std::fixed<<std::setprecision(14);
    auto logPtr=m.karaLog;
    for(; logPtr!=nullptr
#ifdef SANITYCHECK
            &&(!std::isnan(logPtr->d[1][1]))
#endif
            ; logPtr=logPtr->tugi)
        info.dataf << logPtr->d << std::endl;
    info.dataf.close();
    info.scriptf.close();
    return d::conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}

std::string animate(const d::polarmono& m, d::conn::sage::settings::files<d::conn::sage::settings::gif>& info) {
    info.scriptf<<"#!/usr/bin/env sage\n";
    info.scriptf<<"import sys\n";
    info.scriptf<<"from sage.all import *\n";
    info.scriptf<<"# both cartesian\n";
    info.scriptf<<"xs=[]\n";
    info.scriptf<<"vs=[]\n";
    info.scriptf<<"def parseData():\n";
    info.scriptf<<"    E.<x,y> = EuclideanSpace(2)\n";
    info.scriptf<<"    cartesian = E.cartesian_coordinates()\n";
    info.scriptf<<"    polar.<r,t> = E.polar_coordinates()\n";
    info.scriptf<<"    # Since all precision are fixed, we're going lazy\n";
    info.scriptf<<"    for ln in sys.stdin:\n";
    info.scriptf<<"        ln=ln.rstrip()\n";
    info.scriptf<<"        x=sage_eval(ln[2:38])\n";
    info.scriptf<<"        xs.append(E.coord_change(polar, cartesian)(x[0], x[1]))\n";
    info.scriptf<<"        v=sage_eval(ln[42:79])\n";
    info.scriptf<<"        vs.append(E.coord_change(polar, cartesian)(v[0], v[1]))\n";
    info.scriptf<<"def main():\n";
    info.scriptf<<"    parseData()\n";
    info.scriptf<<"    frames=[]\n";
    info.scriptf<<"    for i in range(len(xs)):\n";
    info.scriptf<<"        frames.append(point(xs[i])+line([xs[i], xs[i]+vs[i]], color=\"red\"))\n";
    info.scriptf<<"    Gph=animate(frames)\n";
    info.scriptf<<"    Gph.save(filename=sys.argv[1])\n";
    info.dataf <<std::fixed<<std::setprecision(14);
    auto logPtr=m.karaLog;
    for(; logPtr!=nullptr; logPtr=logPtr->tugi)
        info.dataf << logPtr->d << std::endl;
    info.dataf.close();
    info.scriptf.close();
    return d::conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}

void calc() {
}

std::pair<d::polarcoord, d::polarcoord> runSnell(d::polarmono& m, const d::numerical::compact::func1d<double, DATAAMOUNT>& v) {
    // init log
    m.karaLog=new d::Karabinerhaken<d::polarmono>(m);
    auto karaLog=m.karaLog;
    auto curVel=v(m[0][0]*std::sin(m[0][1]));
    double dt=1e-2; // Reducing from 1e-4 to compress data size
    auto prev=m[0];
    //std::cerr << m[0];
    while(m[0].cartesian()[1]>-singleSideThickness-.4) {
        // check at interface, update velocity
        auto nowAng=m[1][1];
        auto newVel=v(m[0][0]*std::sin(m[0][1]));
        auto delAng=refrac(nowAng, curVel, newVel)-nowAng;
        std::cout << "vel="<<newVel<<", access="<<m[0][0]*std::sin(m[0][1])<<std::endl;
        curVel=newVel;
        std::cout << delAng << ", " << curVel << std::endl;
        // move one step
        prev=m[0];
        m[0]+=m[1].rotate(delAng)*dt;
        m.t+=dt;
        // log
        karaLog=(new d::Karabinerhaken<d::polarmono>(m))->insertAfter(karaLog);
        std::cout << m << std::endl;
    }
    return std::make_pair(prev, m[0]);
}

int main() {
    double inboundAngle, inboundVel, outboundVel;
    std::cin >> inboundAngle;

    d::R range(-singleSideThickness-.5, singleSideThickness+.5);
    d::numerical::compact::func1d<double, DATAAMOUNT> v([](double x){return x>0?299792458.:2.25e8;}, range);
    std::cout << "range=["<<range.von()<<", "<<range.zu()<<"]\n";
    //d::numerical::compact::func1d<double, DATAAMOUNT> v([](double x){ return std::erf(x)*12.24+20.; }, range);
    noNegInFunc(v);
    d::polarmono m;
    //m[0]=d::polarcoord(singleSideThickness, M_PI/2.)+d::polarcoord(.4, M_PI/2.+inboundAngle);
    m[0]=d::polarcoord(singleSideThickness+.4, M_PI/2.+inboundAngle);
    m[1]=d::polarcoord(singleSideThickness+.4, -M_PI/2.+inboundAngle);
    std::cout << "Init: "<<m<<std::endl;
    auto [prevOut, res]=runSnell(m, v);
    std::cout << "Res : "<<m<<std::endl;
    d::compact::line inboundRay(m.karaLog->d[0], m.karaLog->tugi->d[0]),
        outboundRay(res, prevOut);
    std::cout << "Intersecting angle="<<(d::deg)(inboundRay.ang(outboundRay))<<std::endl;
    //d::conn::sage::settings::files<d::conn::sage::settings::png> gph;
    //d::conn::sage::settings::files<d::conn::sage::settings::png> fgph;
    //std::cout << "Function v(x): \n"<<fgph<<"\nPath: \n"<<gph<<std::endl;
    //std::cout << plot(v, fgph) << std::endl << plot(m, gph) << std::endl;
#ifdef HOLD
    double t;
    std::cin >> t;
#endif
    //assert((inboundRay.ang(outboundRay)-(inboundAngle+M_PI-refrac(inboundAngle, v(range.von()), v(range.zu()))))<1e-12);
    std::cout << inboundRay.ang(outboundRay)<<std::endl<<(inboundAngle+M_PI-refrac(inboundAngle, v(range.von()), v(range.zu())))<<std::endl;
    //assert(res[0]==outboundCheck[0]);
    return 0;
}
