#include<cls.hh>
#include<plot.hh>
#include<bits/stdc++.h>

std::string d::conn::sage::plot(cov& f, conn::sage::settings::files<d::conn::sage::settings::png>& info) {
    info.scriptf<<"#!/usr/bin/env sage\n";
    info.scriptf<<"import sys\n";
    info.scriptf<<"from sage.all import *\n";
    info.scriptf<<"def colorTile(v):\n";
    info.scriptf<<"    return polygon([v+d for d in [vector(x) for x in [(-0.5, -0.5),(-0.5, 0.5),(0.5,0.5),(0.5, -0.5)]]],alpha=0.5)\n";
    info.scriptf<<"def main():\n";
    info.scriptf<<"    ln=-2\n";
    info.scriptf<<"    rn=[]\n";
    info.scriptf<<"    Gph=Graphics()\n";
    info.scriptf<<"    for line in sys.stdin:\n";
    info.scriptf<<"        line=line.rstrip()\n";
    info.scriptf<<"        ln+=1\n";
    info.scriptf<<"        if(ln==-1): \n";
    info.scriptf<<"            rn=line.split(\"=>\")\n";
    info.scriptf<<"            rn=[\"vector(\"+x+\")\" for x in rn]\n";
    info.scriptf<<"            rn=[sage_eval(x) for x in rn]\n";
    info.scriptf<<"            continue\n";
    info.scriptf<<"        i=0\n";
    info.scriptf<<"        for b in line:\n";
    info.scriptf<<"            if(int(b)==1):\n";
    info.scriptf<<"                Gph+=colorTile(rn[0]+vector((ln, i)))\n";
    info.scriptf<<"            i+=1\n";
    info.scriptf<<"    print(rn)\n";
    info.scriptf<<"    fnN=sys.argv[1]\n";
    info.scriptf<<"    Gph.save(fnN,dpi=1224, xmin=rn[0][0], xmax=rn[1][0], ymin=rn[0][1], ymax=rn[1][1], aspect_ratio=1)\n";
    info.scriptf<<"main()\n";
    info.dataf<<f;
    info.dataf.close();
    info.scriptf.close();
    return conn::bash::exec("sage "+info.script+" "+info.plot+" < "+info.data);
}

template std::string d::conn::sage::anime(const d::dyn::mono<float, true>&, d::conn::sage::settings::files<d::conn::sage::settings::gif>&, di shadowFrames=0);
template std::string d::conn::sage::anime(const d::dyn::mono<double, true>&, d::conn::sage::settings::files<d::conn::sage::settings::gif>&, di shadowFrames=0);
template std::string d::conn::sage::anime(const d::dyn::mono<long double, true>&, d::conn::sage::settings::files<d::conn::sage::settings::gif>&, di shadowFrames=0);
