#include<oricoord.hh>

inline bool check(const d::polarcoord& res, const d::compact::coord<double, 2>& correct) {
    double EPS = 1e-12;
    d::compact::coord<double, 2>  resC(res);
    std::cout << "result ="<<resC<<" "<<res<<std::endl<<"correct="<<correct<<std::endl;
    return std::abs(resC[0]-correct[0])<EPS && std::abs(resC[1]-correct[1])<EPS;
}

int main() {
    d::polarcoord a(1, 0), b(1, d::deg(60));
    d::compact::coord<double, 2> c(a), d(b);
    std::cout << a << std::endl << b << std::endl;
    if(!check(a+b, c+d)) throw "Incorrect!";
    if(!check(a-b, c-d)) throw "Incorrect!";
    double r=1.2;
    if(!check(a*r, c*r)) throw "Incorrect!";
    if(!check(a/r, c/r)) throw "Incorrect!";
    return 0;
}
