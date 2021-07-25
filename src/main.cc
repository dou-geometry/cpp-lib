#include"../lib/numerical/integration.hh"
#include<string>
#include<iostream>

int main(int argc, char **argv) {
    auto f=[](d::coord<double> x) { return sin(x[0]); };
    std::function<double(d::coord<double>)> ff=f;
    d::line<double> l(d::coord<double>({0}), d::coord<double>({1}));
    std::cout << d::numerical::integrate(l, ff) << std::endl;
	return 0;
}
