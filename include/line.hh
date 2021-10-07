#ifndef __STRUCT_LINE__
#define __STRUCT_LINE__
#include<coord.hh>
#include<units.hh>
#include<tuple>
#include<cassert>
#include<cmath>
namespace d {
template<typename L>
struct line {
    d::coord<L> s, t, d;
    L length;
    line(d::coord<L> a, d::coord<L> b): s(a), t(b), d((b-a).unit()), length((b-a).norm()) {}
    line(const line<L> &other): s(other.d), t(other.t), d(other.d), length(other.length) {}
    //line(line<T> &&other) noexcept: d(std::exchange(other.d, nullptr)), dim(std::exchange(other.dim,(di)0)) {}
    ~line() = default;
    std::tuple<double, double> standard() const {
        assert(d.dim==2);
        double a=d[1]/d[0];
        double b=s[1]-a*s[0];
        return std::forward_as_tuple(a, b);
    }
    double dist(const d::coord<L> Punkt) {
        double tt=(Punkt-s).dot(d);
        auto oLP=s+d*tt;
        return (Punkt-oLP).norm();
    }
    double angcos(const d::line<L>& ln) const {
        auto [a, b]=this->standard();
        auto [c, f]=ln.standard();
        // ax+b==cx+d
        double x=(f-b)/(a-c), y=a*x+b;
        d::coord<double> intersect({x, y});
        auto p=this->s-intersect, q=ln.s-intersect;
        double pdq=p.dot(q);
        return (pdq/p.norm()/q.norm());
    }
    friend double angcos(const d::line<L>& a, const d::line<L>& b) {
        return a.angcos(b);
    }
    inline d::rad ang(const d::line<L>& ln) const {
        //return arccos(this->angcos(ln));
        //auto [a, b]=this->standard();
        //auto [c, d]=ln.standard();
        // ax+b==cx+d
        //double x=(d-b)/(a-c), y=a*x+b;
        //d::coord<double> intersect({x, y});
        //auto p=this->s-intersect, q=ln.s-intersect;
        //double pdq=p.dot(q);
        //return std::acos(pdq/p.norm()/q.norm());
        return std::acos(this->d.dot(ln.d));
    }
    static inline d::rad ang(const d::line<L>& a, const d::line<L>& b) {
        return a.ang(b);
    }
    inline d::rad ang() const {
        return std::atan(d[1]/d[0]);
    }
};

}

namespace d::compact {
struct line {
    d::compact::coord<double, 2> s, t, d;
    double length;
    line(d::compact::coord<double, 2> a, d::compact::coord<double, 2> b): s(a), t(b), d((b-a).unit()), length((b-a).norm()) {}
    line(const line &other): s(other.d), t(other.t), d(other.d), length(other.length) {}
    line(double slope, double shift): length(1),
        s(d::compact::coord<double, 2>({0., shift})),
        t(d::compact::coord<double, 2>({1., slope+shift})),
        d(d::compact::coord<double, 2>({1., slope+shift}).unit()) {}
    ~line() = default;
    std::tuple<double, double> standard() const {
        double a=d[1]/d[0];
        double b=s[1]-a*s[0];
        return std::forward_as_tuple(a, b);
    }
    double dist(const d::compact::coord<double, 2> Punkt) {
        double tt=(Punkt-s).dot(d);
        auto odoubleP=s+d*tt;
        return (Punkt-odoubleP).norm();
    }
    double angcos(const d::compact::line& ln) const {
        auto [a, b]=this->standard();
        auto [c, f]=ln.standard();
        // ax+b==cx+d
        double x=(f-b)/(a-c), y=a*x+b;
        d::compact::coord<double, 2> intersect({x, y});
        auto p=this->s-intersect, q=ln.s-intersect;
        double pdq=p.dot(q);
        return (pdq/p.norm()/q.norm());
    }
    friend double angcos(const d::compact::line& a, const d::compact::line& b) {
        return a.angcos(b);
    }
    inline d::rad ang(const d::compact::line& ln) const {
        //return arccos(this->angcos(ln));
        //auto [a, b]=this->standard();
        //auto [c, d]=ln.standard();
        // ax+b==cx+d
        //double x=(d-b)/(a-c), y=a*x+b;
        //d::compact::coord<double, 2> intersect({x, y});
        //auto p=this->s-intersect, q=ln.s-intersect;
        //double pdq=p.dot(q);
        //return std::acos(pdq/p.norm()/q.norm());
        return std::acos(this->d.dot(ln.d));
    }
    static inline d::rad ang(const d::compact::line& a, const d::compact::line& b) {
        return a.ang(b);
    }
    inline d::rad ang() const {
        return std::atan(d[1]/d[0]);
    }
    d::compact::coord<double, 2> intersect(const d::compact::line& l) {
        double ta=d[1]/d[0], la=l.d[1]/l.d[0];
        double tb=s[1]-ta*s[0], lb=l.s[1]-la*l.s[0];
        // ta*x+tb=la*x+lb
        // (ta-la)*x==lb-tb
        double x=(lb-tb)/(ta-la);
        return d::compact::coord<double, 2>({x, ta*x+tb});
    }
};
static const line yAxis=line(d::compact::coord<double, 2>({0, 0}),
        d::compact::coord<double, 2>({0, 1}));
}

#endif
