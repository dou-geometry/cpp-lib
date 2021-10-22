#include<sys.hh>

int main() {
    /* System setup:
     * whole system: [-2, 2]
     * inteface: [-1, 1]
     */
    d::dou::compact::sys<2, 24> s(-2., 2.);
    std::cout << "Search" << s(d::compact::coord<double, 2>({1,2})) << std::endl;
    return 0;
}
