#include<translate.hh>
#include<mono.hh>

template d::coord<double> d::translate(d::coord<double>, const d::coord<double>&);
template d::dyn::mono<double, true> d::translate(d::dyn::mono<double, true>, const d::coord<double>&);
template d::dyn::mono<double, false> d::translate(d::dyn::mono<double, false>, const d::coord<double>&);
