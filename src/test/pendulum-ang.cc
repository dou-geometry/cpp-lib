#include"../lib/dou/geo/rk4.hh"
#include <cmath>
#include<iostream>

#define G 9.80665

/* Pendulum Simulation
 * Angle-verion
 * Parameter: [r, ang]
 */
template<typename R, typename F>
concept x1 = requires(const R &r, const F &f) {
    std::convertible_to<F, std::function<typename std::decay<decltype(r[0])>::type(typename std::decay<decltype(r[0])>::type)>>;
    {f(r)}->std::same_as<typename std::decay<decltype(r[0])>::type>;
    std::convertible_to<R, typename std::decay<decltype(r[0])>::type>;
};
template<typename R, typename F>
concept x2 = requires(const R &r, const F &f) {
    std::convertible_to<F, std::function<typename std::decay<decltype(r)>::type(typename std::decay<decltype(r)>::type)>>;
    {f(r)}->std::same_as<typename std::decay<decltype(r)>::type>;
    std::convertible_to<R, typename std::decay<decltype(r)>::type>;
};

void test(d::dyn::mono<double, true> a) {
    return;
}

int main() {
    auto a=[](d::coord<double> x) { return d::coord<double>({0, -G/x[0]*std::sin(x[1])}); };
    d::coord<double> d({1, 2}), b({2, 4}), c({2, 0});
    d::dyn::mono<double, true> m(2, d, b, c);
    test(m);
    std::cout << ":::" << std::endl;
    std::cout << m.order << std::endl;
    std::cout << m[0] << std::endl;
}
