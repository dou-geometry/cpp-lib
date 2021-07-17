#ifndef __CAR_LINEAR_MONO_HPP__
#define __CAR_LINEAR_MONO_HPP__
namespace d {
    template<typename G>
        struct mono {
            coord<G> x, v;
            mono(): mono(2) {}
            mono(di dim): x(dim), v(dim) {}
            mono(coord<G> pos, coord<G> vel): x(pos), v(vel) {}
            friend ostream& operator<<(ostream& os, mono& a) {
                os << "x="<<a.x<<"; v="<<a.v;
                return os;
            }
        };
}
#endif
