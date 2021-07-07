#ifndef __STRUCT_LINE__
#define __STRUCT_LINE__

template<typename L>
struct line {
    coord<L> s, t, d;
    line(coord<L> a, coord<L> b): s(a), t(b), d((b-a).unit()){}
    ~line() {
        s.~coord();
        t.~coord();
    }
    double dist(const coord<L> Punkt) {
        double t=(Punkt-s).dot(d);
        auto oLP=s+d*t;
        return (Punkt-oLP).norm();
    }
};

#endif
