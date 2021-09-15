#include<oricoord.hh>

inline double d::oricoord::norm() const { return d[0]; }
inline double d::oricoord::norm2() const { return d[0]*d[0]; }
d::oricoord& d::oricoord::pow(double p) {
    d[0]=std::pow(d[0], p);
    return *this;
}
d::oricoord d::oricoord::pow(double p) const {
    auto res(*this);
    res[0]=std::pow(res[0], p);
    return res;
}
d::oricoord d::oricoord::unit() const {
            auto cpy=*this;
            cpy[0]=1;
            return cpy;
        }
d::oricoord d::oricoord::abs() const {
            oricoord res(this->dim);
            res[0]=fabs(res[0]);
            return res;
        }
