#include"./rotate.hh"
#include"../dyn/mono.hh"

template d::coord<double> d::rotate(d::coord<double>, double);
template d::compact::coord<double, 2> d::rotate(d::compact::coord<double, 2>, double);

template d::dyn::mono<double, true> d::rotate(d::dyn::mono<double, true>, double);
template d::dyn::mono<double, false> d::rotate(d::dyn::mono<double, false>, double);
template d::dyn::compact::mono<double, 1, 2, true> d::rotate(d::dyn::compact::mono<double, 1, 2, true>, double);
template d::dyn::compact::mono<double, 2, 2, true> d::rotate(d::dyn::compact::mono<double, 2, 2, true>, double);
template d::dyn::compact::mono<double, 1, 2, false> d::rotate(d::dyn::compact::mono<double, 1, 2, false>, double);
template d::dyn::compact::mono<double, 2, 2, false> d::rotate(d::dyn::compact::mono<double, 2, 2, false>, double);
