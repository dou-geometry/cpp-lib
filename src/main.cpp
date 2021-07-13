#include"../include/cls.hpp"
#include<string>
#include<iostream>

int main(int argv, char **argv) {
    d::cov f(d::coord<double>({12, 12}));
    d::line<double> l(d::coord<double>({1, 1}), d::coord<double>({1, 2}));
    std::cout << f.calc(l) << std::endl;
	return 0;
}
