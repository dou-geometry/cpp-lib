#include"../numerical/rk4.cpp"
// Explicit Instantiation
namespace d::numerical::rk4 {
    template coord<float> run(coord<float>, &, const double);
    template coord<double> run(coord<double>, &, const double);
    template coord<long double> run(coord<long double>, &, const double);
    template mono<float> run(mono<float>, &, const double);
    template mono<double> run(mono<double>, &, const double);
    template mono<long double> run(mono<long double>, &, const double);
}
