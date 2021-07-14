#include"../../include/numerical/integration.hpp"
#include<cmath>
#include <functional>
#include<iostream>

template<typename T, typename L>
T d::numerical::integrate(const d::line<T>& l, const L& f) {
    auto sum=[&f, &l](di t) {
        const ull divi=pow(4, t);
        std::cout << divi << std::endl;
        const double dl=l.length/((double)divi);
        double res=0;
        for(di i=0; i<divi; i++)
            res+=f(l.s+l.d*dl*i)*dl;
        return res;
    };
    di i=5;
    d::numerical::dp<T> res;
    res[i]=sum(i);
    do {
        i++;
        res[i]=sum(i);
        std::cout << res[i] << std::endl;
    } while(std::abs(res[i]-res[i-1])>numerical::EPS);
    std::cout << std::endl;
    return (T)res[i];
};
template double d::numerical::integrate(const d::line<double>&, const std::function<double(d::coord<double>)>&);

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
