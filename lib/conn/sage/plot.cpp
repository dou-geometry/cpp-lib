#include"../../../include/conn/sage/settings.hpp"
#include<bits/stdc++.h>

namespace d::conn::sage {
    void plot(conn::sage::settings::files& info) {
        info.scriptf<<"#!/usr/bin/env sage\n";
        info.scriptf<<"import sys\n";
        info.scriptf<<"from sage.all import *\n";
        info.scriptf<<"def readFromStdin():\n";
        info.scriptf<<"    pts=[]\n";
        info.scriptf<<"    for line in sys.stdin:\n";
        info.scriptf<<"        line=line.rstrip()\n";
        info.scriptf<<"        pts.append(sage_eval('vector('+line+')'))\n";
        info.scriptf<<"    return pts\n";
        info.scriptf<<"def plotPts(l, connect=False):\n";
        info.scriptf<<"    gph=Graphics()\n";
        info.scriptf<<"    for i in range(len(l)-(1 if connect else 0)):\n";
        info.scriptf<<"        if connect: gph+=line([l[i], l[i+1]])\n";
        info.scriptf<<"        else: gph+=point(l[i])\n";
        info.scriptf<<"    return gph\n";
        info.scriptf<<"def savePlot(G, view=False, p='./graph/'):\n";
        info.scriptf<<"    import time\n";
        info.scriptf<<"    fnN=p+time.strftime('%Y.%m.%d-%H:%M:%S')+'.png'\n";
        info.scriptf<<"    save(G,fnN,dpi=1225,axes=False,aspect_ratio=1)\n";
        info.scriptf<<"    if view: os.system('gwenview '+fnN+' &')\n";
        info.scriptf<<"def main():\n";
        info.scriptf<<"    savePlot(plotPts(readFromStdin(), True), True)\n";
        info.scriptf<<"main()\n";
    }
}
