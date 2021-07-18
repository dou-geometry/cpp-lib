#pragma once

#include"../cls/coord.hh"
#include <type_traits>

namespace d::dyn {
    template<typename T, bool logIncrPromise=false>
        struct mono {
            double t;
            mono* log=nullptr;
            coord<T> pos, vel;
            mono(): t(0), pos(1, (T)0), vel(1, (T)0) {}
            mono(di d): t(0), pos(d, (T)0), vel(d, (T)0) {}
            mono(coord<T> p): t(0), pos(p), vel(p.dim, (T)0) {}
            mono(coord<T> p, coord<T> v): t(0), pos(p), vel(v) {
                static_assert(p.dim==v.dim, "d::dyn::mono's position and velocity coord has different dimension");
            }
            template<typename X> requires std::integral<X> mono(coord<T> p, coord<T> v, X it): pos(p), vel(v), t(it) {
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
            mono& operator[](double t) { // This assumes the log follows const dt
                double dt=this->log[1]-(this->log[0]);
                t-=this->log[0];
                return this->log[(int)(t/dt)];
            }
            mono& operator()(double t) { // This preforms check if t matches, if failed it'll be followed by binary search
                double dt=this->log[1]-(this->log[0]);
                t-=this->log[0];
                int id=t/dt;
                if constexpr(logIncrPromise) { return this->log[id]; }
                else {
                    if((this->log[id]).t==t) {
                        return this->log[id];
                    } else {
                        while((this->log[id]).t!=t) {
                            id-=((this->log[id]).t)>t?id/2:-1;
                        }
                        return this->log[id];
                    }
                }
            }
            friend ostream& operator<<(ostream& os, const mono& x) {
                os << "t="<<x.t<<"; pos="<<x.pos<<"; vel="<<x.vel;
                return os;
            }
            template<typename C> operator d::coord<C>() const { return pos; }
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
