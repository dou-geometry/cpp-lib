#include<orimono.hh>
d::polarmono::polarmono(const d::polarcoord& x, const d::polarcoord& v) {
    d=(d::polarcoord*)malloc(sizeof(d::polarmono)*2);
    new(d)d::polarcoord(x);
    new(d+1)d::polarcoord(v);
}
d::polarmono::~polarmono() {
    (d+1)->~polarcoord();
    d->~polarcoord();
    free(d);
    delete karaLog;
}
d::polarmono::polarmono(const d::polarmono& m) {
    t=m.t;
    d=(d::polarcoord*)malloc(sizeof(d::polarmono)*2);
    new(d)d::polarcoord(*(m.d));
    new(d+1)d::polarcoord(*(m.d+1));
}
d::polarmono::polarmono(polarmono&& m) noexcept: t(std::exchange(m.t, 0)), karaLog(std::exchange(m.karaLog, nullptr)) {
    std::swap(d, m.d);
}
d::polarmono& d::polarmono::operator=(const d::polarmono& m) {
    if(this==&m) return *this;
    t=m.t;
    d[0]=m.d[0];
    d[1]=m.d[1];
    return *this;
}
d::polarmono& d::polarmono::operator=(polarmono&& m) noexcept {
    if(this==&m) return *this;
    delete karaLog;
    t=m.t;
    d[0]=m.d[0];
    d[1]=m.d[1];
    return *this;
}
d::polarcoord& d::polarmono::operator[](int i) {
    return d[i];
}
d::polarcoord d::polarmono::operator[](int i) const {
    return d[i];
}
d::compact::mono<2> d::polarmono::cartesian() const {
    return d::compact::mono<2>(this->t, this->d->cartesian(), this->d[1].cartesian());
}
namespace d { std::ostream& operator<<(std::ostream& os, const d::polarmono& m) {
    os << "x="<<m.d[0]<<", v="<<m.d[1]<<", t="<<m.t;
    return os;
} }
