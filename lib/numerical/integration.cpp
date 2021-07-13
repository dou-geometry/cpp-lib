#include"../../include/numerical/integration.hpp"

template<typename T>
T d::numerical::integrate(const line<T>& l, const field<T>& f, di m=1) {
    // calc to resolution++=>diff<EPS
    // for i++: pow(2, i) or i?
    di i=1;
    cov c(f, i);
    //calc once here first
    d::numerical::dp res;
    do {
        i++;
        c.resolution++;
    } while(abs(res[i]-res[i-1])<=d::numerical::EPS);
}

template<typename T>
T d::numerical::integrate(const coord<T>& s, const coord<T>& t, const field<T>& f, di m) {
    cov c(f, m);
}

template<typename T>
T d::numerical::integrate(const coord<T>& s, const coord<T>& t, const field<T>& f, di ms, di mt) {
    T res[mt-ms+1];
    for(di i=ms, i<=mt, i++)
        res[i-ms]=d::numerical::integrate(s, t, f, i);
}

template<typename T>
T d::numerical::integrate(const coord<T>& s, const coord<T>& t, const field<T>& f, std::tuple<di, di> tup) {
    auto [a, b] = tup;
    return d::numerical::integrate(s, t, f, a, b);
}
