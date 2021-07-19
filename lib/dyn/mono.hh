#pragma once

#include"../cls/coord.hh"
#include"../concepts/nonDim.hh"
#include <type_traits>
#define di long unsigned int
#define ull unsigned long long int

namespace d::dyn {
    template<typename T, bool logIncrPromise=false>
        struct mono {
            const int order=2;
            double t;
            mono* log=nullptr;
            coord<T> *d=new coord<T>[3];
            coord<T> &pos=d[0], &vel=d[1], &acc=d[2];
            mono(): t(0), pos(1, (T)0), vel(1, (T)0), acc(1, (T)0) {}
            mono(di d): order(2), t(0), pos(d, (T)0), vel(d, (T)0), acc(d, (T)0) {}
            mono(di d, initializer_list<coord<T>> l) {}
            mono(initializer_list<coord<T>> l) {}
            // change to variadic template?
            // And auto add empty d::coord<T>(dim) if variadic length<dim
            // remember d[order+1];
            template<typename X> requires d::nonDim<X> mono(X it, initializer_list<coord<T>> l) {}
            template<typename X> requires d::nonDim<X> mono(X it, di d, initializer_list<coord<T>> l) {}
            template<typename X> requires d::nonDim<X> mono(di d, X it, initializer_list<coord<T>> l): mono(it, d, l) {}
            ~mono() {
                delete[]log;
                delete[]d;
            }




            mono(coord<T> p): t(0), pos(p), vel(p.dim, (T)0), acc(p.dim, (T)0) {}
            mono(coord<T> p, coord<T> v): t(0), pos(p), vel(v), acc(v.dim, (T)0) {
                static_assert(p.dim==v.dim, "d::dyn::mono's position and velocity coord has different dimension");
            }
            mono(coord<T> p, coord<T> v, coord<T> a): t(0), pos(p), vel(v), acc(a) {
                static_assert(p.dim==v.dim, "d::dyn::mono's position and velocity coord has different dimension");
                static_assert(v.dim==a.dim, "d::dyn::mono's velocity and acceleration coord has different dimension");
            }
            template<typename X> requires std::integral<X> mono(X it, coord<T> p, coord<T> v, coord<T> a): pos(p), vel(v), t(it), acc(a) {
                static_assert(p.dim==v.dim, "d::dyn::mono's position and velocity coord has different dimension");
                static_assert(v.dim==a.dim, "d::dyn::mono's velocity and acceleration coord has different dimension");
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
            inline mono& operator[](const int& i) {
                if (i==0) return pos;
                if (i==1) return vel;
                if (i==2) return acc;
                // return d::coord<T>(pos.dim);
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
