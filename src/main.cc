#include"../lib/cls/coord.hh"
#include"../lib/manip/translate.hh"
#include"../lib/manip/rotate.hh"
#include<string>
#include<iostream>
#include<cmath>

int main(int argc, char **argv) {
    d::coord<double> x({1.2, 2.4});
    x=d::translate(x, x);
    std::cout << x << std::endl;
    x=d::rotate(x, M_PI);
    std::cout << x << std::endl;
	return 0;
}
