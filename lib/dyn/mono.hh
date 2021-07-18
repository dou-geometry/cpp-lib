#pragma once

#include"../cls/coord.hpp"
#include <type_traits>

namespace d::dyn {
    template<typename T>
        struct mono {
            double t;
            mono* log=nullptr;
            coord<T> pos, vel;
            mono(): t(0), pos(1, (T)0), vel(1, (T)0) {}
            mono(coord<T> p): t(0), pos(p), vel(p.dim, (T)0) {}
            mono(coord<T> p, coord<T> v): t(0), pos(p), vel(v) {
                static_assert(p.dim==v.dim, "d::dyn::mono's position and velocity coord has different dimension");
            }
            mono& operator=(const mono<T> &other) {
                if(this==&other) return *this;
                // Basically we aren't replacing logs
                // Only copying t, pos, vel
                t=other.t; // As order in array are only relative to the log[0]
                pos=other.pos;
                vel=other.vel;
                return *this;
            }
            mono& operator=(mono<T> &&other) noexcept {
                swap(t, other.t);
                swap(log, other.log);
                swap(pos, other.pos);
                swap(vel, other.vel);
                return *this;
            }
            mono& operator+=(double dt, d::coord<T> dx, d::coord<T> dv) {
                static_assert(dx.dim==pos.dim, "d::dyn::mono::operator+= dx.dim!=pos.dim");
                static_assert(dv.dim==vel.dim, "d::dyn::mono::operator+= dv.dim!=vel.dim");
                t+=dt;
                pos+=dx;
                vel+=dv;
                return *this;
            }
            mono& operator+=(double dt, d::coord<T> uv) {
                // requires vel vector ratio to unit time
                static_assert(uv.dim==pos.dim, "d::dyn::mono::operator+= uv.dim not same with mono's dim");
                pos+=uv*dt;
                t+=dt;
                v=uv;
                return *this;
            }
            template<typename X> requires std::integral<X> mono(coord<T> p, coord<T> v, X it): mono(p, v), t(it) {}
        };
    template<typename C>
        concept Loggable = requires(C& x) {
            {*(x.log)}->std::common_with<C>;
        };
    template<typename C>
        concept DummyLoggable = requires(C& x) {
            {*(x.log)}->std::common_with<C>;
            // add another to check if direct overwriting (through operator=) will trigger the logging?
        };
}
