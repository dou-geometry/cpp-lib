#include<oricoord.hh>

inline double d::polarcoord::norm() const { return d[0]; }
inline double d::polarcoord::norm2() const { return d[0]*d[0]; }
d::polarcoord& d::polarcoord::pow(double p) {
    d[0]=std::pow(d[0], p);
    return *this;
}
d::polarcoord d::polarcoord::pow(double p) const {
    auto res(*this);
    res[0]=std::pow(res[0], p);
    return res;
}
d::polarcoord d::polarcoord::unit() const {
    auto cpy=*this;
    cpy[0]=1;
    return cpy;
}
d::polarcoord d::polarcoord::abs() const {
    polarcoord res(2);
    res[0]=fabs(res[0]);
    return res;
}
d::polarcoord& d::polarcoord::operator+=(const d::polarcoord &r) {
    polarcoord res(2);
    auto oriR=d[0];
    d[0]=(oriR*oriR)+(r[0]*r[0])-2.*oriR*r[0]*std::cos(r[1]-d[1]);
    d[1]=d[1]+std::atan2(r[0]*std::sin(r[1]-d[1]), oriR+r[0]*std::cos(r[1]-d[1]));
    return *this;
}
std::ostream& operator<<(std::ostream& os, const d::polarcoord& crd) {
    os << "[" << crd[0];
    os << ", " << crd[1];
    os << "]";
    return os;
}
void d::polarcoord::print(int precision) {
    printf("[%.*lf", precision, *d);
    printf(", %.*lf", precision, *(d+1));
    printf("]\n");
}
void d::polarcoord::input() {
    for(di i=0; i<2; i++) {
        std::cin >> d[i];
    }
}
void d::polarcoord::input(d::polarcoord &x) {
    std::cout << "Please enter polar coordinate with each parameter seperated by space: ";
    x.input();
}
d::compact::coord<double, 2> d::polarcoord::cartesian() const {
    return d::compact::coord<double, 2>({d[0]*std::cos(d[1]), d[0]*std::sin(d[1])});
}
