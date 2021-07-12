#include"../include/conn/sage/plot.hpp"
#include"../include/cls.hpp"
#include<string>
#include<iostream>

int main() {
	d::conn::sage::settings::files x("/tmp/plot.png");
	d::cov f(d::coord<int>({12, 24}));
	std::cout << f.IDzuCoord(f.coordZuID(d::coord<double>({2, 0}))) << std::endl;
	std::cout << f.multiplier << std::endl;
	std::cout << x << std::endl;
	f[10]=true;
	std::cout << d::conn::sage::plot(f, x) << std::endl;
	return 0;
}
