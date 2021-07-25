#include"../lib/numerical/rk4.hh"
#include <cmath>
#include<iostream>

double gaussianFunc(double x) { return std::exp(-1*pow(x,2)); }
double gaussianFunc(d::coord<double> x) {
    return std::exp(-1*pow(x.norm(), 2));
}

d::coord<double> f(d::coord<double> x) {
    // The field function
    return d::coord<double>({gaussianFunc(x), 0});
}

int main() {
    //d::dyn::mono<double, true> m(2);
    d::coord<double> m(2);
    std::function<d::coord<double>(d::coord<double>)> cf=f;
    //m=d::numerical::rk4::run(m, f, 10.0);
    std::cout << m << std::endl;
}
