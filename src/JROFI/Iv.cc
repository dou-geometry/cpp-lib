#include"./Iv.hh"

d::Iv::funcPoints::funcPoints(bool(*cond)(const d::dyn::compact::mono<double, 1, 1, true>&), double k, double c) {
    auto dv=[](const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return d::compact::coord<double, 1>({pow(sqrt(1-pow(m[0], 2.)), 3.)});
    };
    d::dyn::compact::mono<double, 1, 1, true> m;
    this->dK=d::numerical::rk4::run<1, false>(m, dv, cond);
    auto cur=this->dK;
    for(cur=cur->tugi; cur->tugi!=nullptr; cur=cur->tugi) cur->d[0][0]/=cur->d.t;
    cur->d[0][0]/=cur->d.t;
    d::Iv::tMax=cur->d.t;
}

d::Karabinerhaken<d::dyn::compact::mono<double, 1, 1, true>>* d::Iv::genMoreOnce(bool(*cond)(const d::dyn::compact::mono<double, 1, 1, true>&), double k, double c) {
    auto dv=[](const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return d::compact::coord<double, 1>({pow(sqrt(1-pow(m[0], 2.)), 3.)});
    };
    auto contPt=d::Iv::data()->end();
    d::dyn::compact::mono<double, 1, 1, true> m(contPt->d);
    contPt->tugi=d::numerical::rk4::run<1, false>(m, dv, cond)->tugi;
    for(; contPt->tugi!=nullptr; contPt=contPt->tugi) contPt->d[0][0]/=(contPt->d.t*k);
    contPt->d[0][0]/=(contPt->d.t*k);
    d::Iv::tMax.store(contPt->d.t);
    return d::Iv::data();
}
