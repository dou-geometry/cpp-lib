#!/usr/bin/env sage

import sys
from sage.all import *


def readFromStdin():
    pts=[]
    for line in sys.stdin:
        line=line.rstrip()
        pts.append(sage_eval('vector('+line+')'))
    return pts

def plotPts(l, connect=False):
    gph=Graphics()
    for i in range(len(l)-(1 if connect else 0)):
        if connect: gph+=line([l[i], l[i+1]])
        else: gph+=point(l[i])
    return gph

def savePlot(G, view=False, p='./graph/'):
    import time
    fnN=p+time.strftime('%Y.%m.%d-%H:%M:%S')+'.png'
    save(G,fnN,dpi=1225,axes=False,aspect_ratio=1)
    if view: os.system('gwenview '+fnN+' &')

def main():
    savePlot(plotPts(readFromStdin(), True), True)

main()
