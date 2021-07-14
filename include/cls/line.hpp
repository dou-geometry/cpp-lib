#ifndef __STRUCT_LINE__
#define __STRUCT_LINE__
#include"./coord.hpp"
namespace d {
template<typename L>
struct line {
    d::coord<L> s, t, d;
    L length;
    line(d::coord<L> a, d::coord<L> b): s(a), t(b), d((b-a).unit()), length((b-a).norm()) {}
    ~line() {
        s.~coord();
        t.~coord();
    }
    double dist(const d::coord<L> Punkt) {
        double t=(Punkt-s).dot(d);
        auto oLP=s+d*t;
        return (Punkt-oLP).norm();
    }
};

}
#endif
