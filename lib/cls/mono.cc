#include<mono.hh>

template struct d::mono<double>;
template struct d::dyn::mono<double, true>;
template struct d::dyn::mono<double, false>;
