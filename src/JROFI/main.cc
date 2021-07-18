#include"../lib/numerical/rk4.hh"
#include <cmath>

double gaussianFunc(double x) { return std::exp(-1*pow(x,2)); }
double gaussianFunc(d::coord<double> x) {
    return std::exp(-1*pow(x.norm(), 2));
}
d::coord<double> gaussianFunc(d::coord<double> x) {
    x.pow(2);
    x*=-1;
    for(di i=0; i<x.dim; i++)
        x[i]=std::exp(x[i]);
    return x;
}


d::coord<double> f(d::coord<double> x) {
    // The field function
    double mag=gaussianFunc(x); // Not sure if it could be put inside
    return d::coord<double>({mag, 0});
}

int main() {
    d::dyn::mono<double, true> m;
    m=d::numerical::rk4(m, f);
}
