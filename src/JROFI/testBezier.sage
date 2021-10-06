# const def
vin, vout=[1, 0.9] # vin>vout
h=2
EPS=1e-12
y, theta, phi=var("y theta phi")
templateP=-1/8*h*((h - 2*y)/h - 2)^2*tan(theta) + 1/8*(h - 2*y)^2*tan(phi)/h

# forall
thin=RR.random_element(0, asin(vout/vin))
tpin=RR.random_element(0, asin(vout/vin))
thout=arcsin(sin(thin)*vout/vin)
tpout=arcsin(sin(tpin)*vout/vin)

# x=RR.random_element(-h/2*tan(asin(vout/vin)), -h/2*tan(asin(vout/vin*vout/vin)))
# or
sy=RR.random_element(-h/2, h/2)

P(y)=templateP(theta=thin, phi=thout) # 
Pp(y)=templateP(theta=tpin, phi=tpout) # path of tpin
sthin=arctan2(1, P.diff()(sy+EPS))
sthout=arctan2(1, P.diff()(sy-EPS))
stpin=arctan2(1, Pp.diff()(sy+EPS))
stpout=arctan2(1, Pp.diff()(sy-EPS))
print(sin(sthin)/sin(sthout)-vin/vout)
print(sin(stpin)/sin(stpout)-vin/vout)
