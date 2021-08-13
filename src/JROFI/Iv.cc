#include"./Iv.hh"

d::IvBackend::funcPoints::funcPoints(bool(*cond)(const d::dyn::compact::mono<double, 1, 1, true>&), double k, double c) {
    auto dv=[](const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return d::compact::coord<double, 1>({pow(sqrt(1-pow(m[0], 2.)), 3.)});
    };
    d::dyn::compact::mono<double, 1, 1, true> m;
    this->dK=d::numerical::rk4::run<1, false>(m, dv, cond);
    auto cur=this->dK;
    for(cur=cur->tugi; cur->tugi!=nullptr; cur=cur->tugi) cur->d[0][0]/=cur->d.t;
    cur->d.log=(d::dyn::compact::mono<double, 1, 1, true>*)malloc(sizeof(cur->d));
    new(cur->d.log)d::dyn::compact::mono<double, 1, 1, true>(cur->d);
    cur->d[0][0]/=cur->d.t;
    d::IvBackend::tMax=cur->d.t;
}

d::Karabinerhaken<d::dyn::compact::mono<double, 1, 1, true>>* d::IvBackend::genMoreOnce(bool(*cond)(const d::dyn::compact::mono<double, 1, 1, true>&), double k, double c) {
    d::IvBackend::data();
    auto dv=[](const d::dyn::compact::mono<double, 1, 1, true>& m) {
        return d::compact::coord<double, 1>({pow(sqrt(1-pow(m[0], 2.)), 3.)});
    };
    auto contPt=d::IvBackend::data()->end();
    d::dyn::compact::mono<double, 1, 1, true> m(*(contPt->d.log));
    contPt->d.log->~mono();
    free(contPt->d.log);
    contPt->tugi=d::numerical::rk4::run<1, false>(m, dv, cond)->tugi;
    for(contPt=contPt->tugi; contPt->tugi!=nullptr; contPt=contPt->tugi) contPt->d[0][0]/=contPt->d.t;
    contPt->d.log=(d::dyn::compact::mono<double, 1, 1, true>*)malloc(sizeof(contPt->d));
    new(contPt->d.log)d::dyn::compact::mono<double, 1, 1, true>(contPt->d);
    contPt->d[0][0]/=(contPt->d.t*k);
    d::IvBackend::tMax.store(contPt->d.t);
    return d::IvBackend::data();
}

double d::Iv(double v) {
    ull key=(ull)(std::round(std::abs(v)*1e4));
    if(key>(ull)(std::round(d::IvBackend::tMax*1e4))) {
        d::IvBackend::ongoing.wait(true);
        d::IvBackend::ongoing.test_and_set();
        d::IvBackend::tMax=v;
        d::IvBackend::genMoreOnce([](const d::dyn::compact::mono<double, 1, 1, true>&m){return m.t>d::IvBackend::tMax;});
        d::IvBackend::ongoing.clear();
        //d::IvBackend::ongoing.notify_all();
    }
    return d::IvBackend::data()->after(key)->d.d[0];
}
