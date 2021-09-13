#ifndef __STRUCT_LINE__
#define __STRUCT_LINE__
#include<coord.hh>
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
    ~line() {
        // perhaps we don't need destructor
    }
    std::tuple<double, double> standard() const {
        assert(d.dim==2);
        double a=d[1]/d[0];
        double b=s[1]-a*s[0];
        return std::forward_as_tuple(a, b);
    }
    double dist(const d::coord<L> Punkt) {
        double t=(Punkt-s).dot(d);
        auto oLP=s+d*t;
        return (Punkt-oLP).norm();
    }
    double angcos(const d::line<L>& ln) const {
        auto [a, b]=this->standard();
        auto [c, d]=ln.standard();
        // ax+b==cx+d
        double x=(d-b)/(a-c), y=a*x+b;
        d::coord<double> intersect({x, y});
        auto p=this->s-intersect, q=ln.s-intersect;
        double pdq=p.dot(q);
        return (pdq/p.norm()/q.norm());
    }
    friend double angcos(const d::line<L>& a, const d::line<L>& b) {
        return a.angcos(b);
    }
    inline double ang(const d::line<L>& ln) const {
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
    static inline double ang(const d::line<L>& a, const d::line<L>& b) {
        return a.ang(b);
    }
    inline double ang() const {
        return std::atan(d[1]/d[0]);
    }
};

}
#endif
