#include"../../include/numerical/integration.hpp"
#include<cmath>

template<typename T>
T d::numerical::integrate(const d::line<T>& l, const field<T>& f, di m=1) {
    // calc to resolution++=>diff<EPS
    // for i++: pow(2, i) or i?
    di i=1;
    cov c(f, i);
    //calc once here first
    numerical::dp<double> res;
    do {
        i++;
        c.resolution++;
    } while(std::abs(res[i]-res[i-1])<=numerical::EPS);
}

template<typename T>
T d::numerical::integrate(const d::coord<T>& s, const d::coord<T>& t, const field<T>& f, di m) {
    cov c(f, m);
}

template<typename T>
T d::numerical::integrate(const d::coord<T>& s, const d::coord<T>& t, const field<T>& f, di ms, di mt) {
    T res[mt-ms+1];
    for(di i=ms; i<=mt; i++)
        res[i-ms]=numerical::integrate(s, t, f, i);
    return res[0];
}

template<typename T>
T d::numerical::integrate(const d::coord<T>& s, const d::coord<T>& t, const field<T>& f, std::tuple<di, di> tup) {
    auto [a, b] = tup;
    return numerical::integrate(s, t, f, a, b);
}
