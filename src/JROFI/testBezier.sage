# const def
vin, vout=[1, 0.9] # vin>vout
h=2
EPS=1e-12

# forall
thin=RR.random_element(0, asin(vout/vin))
tpin=RR.random_element(0, asin(vout/vin))
thout=asin(sin(thin)*vout/vin)
tpout=asin(sin(tpin)*vout/vin)

# x=RR.random_element(-h/2*tan(asin(vout/vin)), -h/2*tan(asin(vout/vin*vout/vin)))
# or
y=RR.random_element(-h/2, h/2)

P(y)= # 
Pp(y)= # path of tpin
