#include"./IgN.hh"
#include<cmath>

double d::Ig(double r, double M) {
    //const double k=2;
    //return std::min(std::abs(M/(std::abs(r)-k)), 1224.);
    return std::max(-12./24.*std::abs(r)+20, 0.);
}
