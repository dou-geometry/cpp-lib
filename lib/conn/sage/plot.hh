#include"../../cls.hh"
#include"./settings.hh"
#include"../bash/stdout.hh"
#include"../../dyn/mono.hh"
#include<string>
#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__
#define di long unsigned int
#define ull unsigned long long int
#define ll long long int
namespace d::conn::sage {
    std::string plot(cov&, settings::files&);
    std::string anime(const d::dyn::mono<double, true>& m, settings::files& info, di shadowFrames=0) {
        std::cout << "Plotting" << std::endl;
        info.scriptf<<"#!/usr/bin/env sage\n";
        info.scriptf<<"import sys\n";
        info.scriptf<<"from sage.all import *\n";
        info.scriptf<<"def parseFrame():\n";
        info.scriptf<<"    fn=0\n";
        info.scriptf<<"    cc=0\n";
        info.scriptf<<"    inFrame=False\n";
        info.scriptf<<"    frames=[]\n";
        info.scriptf<<"    vct=vector((0,0))\n";
        info.scriptf<<"    npt=2*e^(i*pi/2)\n";
        info.scriptf<<"    for ln in sys.stdin:\n";
        info.scriptf<<"        ln=ln.rstrip()\n";
        info.scriptf<<"        if(ln==\"============\"):\n";
        info.scriptf<<"            if(inFrame):\n";
        info.scriptf<<"                fn+=1\n";
        info.scriptf<<"                inFrame=False\n";
        info.scriptf<<"            else:\n";
        info.scriptf<<"                inFrame=True\n";
        info.scriptf<<"                cc=0\n";
        info.scriptf<<"                frames.append(Graphics())\n";
        info.scriptf<<"        else:\n";
        info.scriptf<<"            if(cc==0):\n";
        info.scriptf<<"                vct=vector(sage_eval(ln))\n";
        info.scriptf<<"                npt=vct[0]*e^(i*(vct[1]-pi/2))\n";
        info.scriptf<<"                frames[fn]+=point(npt)\n";
        info.scriptf<<"            if(cc==1):\n";
        info.scriptf<<"                x=sage_eval(ln)\n";
        info.scriptf<<"                frames[fn]+=line([npt, x[0]*e^(i*(x[1]-pi/2))], color=\"blue\")\n";
        info.scriptf<<"            if(cc==2):\n";
        info.scriptf<<"                x=sage_eval(ln)\n";
        info.scriptf<<"                frames[fn]+=line([npt, x[0]*e^(i*(x[1]-pi/2))], color=\"red\")\n";
        info.scriptf<<"            cc+=1\n";
        info.scriptf<<"    return frames\n";
        info.scriptf<<"def main():\n";
        info.scriptf<<"    Gph=animate(parseFrame(), xmin=-2, xmax=2, ymin=-2, ymax=2)\n";
        info.scriptf<<"    Gph.save(filename=sys.argv[1])\n";
        info.scriptf<<"main()\n";
        for(di i=0; i<m.logSize; ++i)
            info.dataf << m.log[i] << std::endl;
        info.dataf.close();
        info.scriptf.close();
        return conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
    }
    template<typename D> std::string point(Karabinerhaken<d::coord<D>>&, settings::files&);
    template<typename D> std::string line(Karabinerhaken<d::coord<D>>&, settings::files&);
}
#include"./plot.tt"
#endif
