#pragma once

#include"../cls/coord.hh"
#include<iostream>
#include <type_traits>
#include<cassert>
#define di long unsigned int
#define ull unsigned long long int

namespace d::dyn {
    template<typename T, bool logIncrPromise=false>
        struct mono {
            di order;
            double t;
            mono* log=nullptr;
            d::coord<T> *d=nullptr;
            //d::coord<T> &pos=d[0], &vel=d[1], &acc=d[2];
            template<typename...Ts>
                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type>
                mono(di ord, Ts...args): order(ord), t(0) {
                    std::cout << "Standard init d::dyn::mono" << std::endl;
                    d=new d::coord<T>[order+1];
                    assert(sizeof...(Ts)<=(order+1)&& "d::dyn::mono initialization error, too many arguments");
                    di i=0;
                    (...,void(d[i++] = args)); // https://stackoverflow.com/a/34569679/8460574
                    for(di i=sizeof...(Ts); i<=order; ++i)
                        d[i]=d::coord<T>(d[0].dim);
                    for(di i=0; i<=order; i++)
                        std::cout << d[i].d << std::endl;
                }
            mono(): mono(1, d::coord<T>(1)) {
                std::cout << "empty mono" << std::endl;
            }
            mono(di dimension): mono(2, d::coord<T>(dimension)) {}
//            template<typename...Ts>
//                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type>
//                mono(Ts...args): mono(sizeof...(Ts)-1, args..., 0.) {}
//            template<typename X, typename...Ts> 
//                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type> && d::nonDim<X>
//                mono(X it, Ts...args): mono(sizeof...(Ts)-1, args..., it) {}
//            template<typename X, typename...Ts> 
//                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type> && d::nonDim<X>
//                mono(X it, di ord, Ts...args): mono(ord, args..., it) {}
//            template<typename X, typename...Ts> 
//                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type> && d::nonDim<X>
//                mono(di ord, X it, Ts...args): mono(ord, args..., it) {}
            ~mono() {
                std::cout << "------------" << std::endl;
                delete[]log;
                delete[]d;
            }





            mono(const mono<T> &other): order(other.order), t(other.t) {
                std::cout << "&()" << std::endl;
                d=new d::coord<T>[order+1];
                if constexpr(other.d!=nullptr) memcpy(d, other.d, sizeof(d::coord<T>)*(order+1));
            }
            mono(mono<T> &&other) noexcept: d(std::exchange(other.d, nullptr)), order(std::exchange(other.order, 0)), t(std::exchange(other.t, 0)), log(std::exchange(other.log, nullptr)) {
                std::cout << "&&()" << std::endl;
            }
            mono& operator=(const mono<T> &other) {
                std::cout << "&=" << std::endl;
                if(this==&other) return *this;
                // Basically we aren't replacing logs
                // Only copying t, pos, vel
                t=other.t; // As order in array are only relative to the log[0]
                order=other.order;
                d=new d::coord<T>[order+1];
                memcpy(d, other.d, sizeof(d::coord<T>)*(order+1));
                return *this;
            }
            mono& operator=(mono<T> &&other) noexcept {
                std::cout << "&&=" << std::endl;
                swap(order, other.order);
                swap(t, other.t);
                swap(log, other.log);
                swap(d, other.d);
                return *this;
            }
            d::coord<T>& operator[](int i) {
                return this->d[i];
            }
            d::coord<T> operator[](int i) const {
                return this->d[i];
            }
//            mono& operator()(double t) { // This preforms check if t matches, if failed it'll be followed by binary search
//                double dt=this->log[1]-(this->log[0]);
//                t-=this->log[0];
//                int id=t/dt;
//                if constexpr(logIncrPromise) { return this->log[id]; }
//                else {
//                    if((this->log[id]).t==t) {
//                        return this->log[id];
//                    } else {
//                        while((this->log[id]).t!=t) {
//                            id-=((this->log[id]).t)>t?id/2:-1;
//                        }
//                        return this->log[id];
//                    }
//                }
//            }
            friend ostream& operator<<(ostream& os, const mono& x) {
                os << "t="<<x.t<<"; pos="<<x[0]<<"; vel="<<x[1];
                return os;
            }
            //template<typename C> operator d::d::coord<C>() const { return pos; }
            template<typename C> operator d::coord<C>() const { return this->d[0]; }
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
