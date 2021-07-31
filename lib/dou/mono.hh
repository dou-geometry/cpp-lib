#pragma once

#include"../cls/coord.hh"
#include"../cls/compact/coord.hh"
#include"../concepts/nonDim.hh"
#include<iostream>
#include <type_traits>
#include<cassert>
#include<functional>
#define di long unsigned int
#define ull unsigned long long int

namespace d::dou {
    struct mono {
    };
}

namespace d::dou::compact {
    template<typename T, di DEorder=2, di dimension=2, bool logIncrPromise=false>
        struct mono {
            double t=0;
            mono* log=nullptr;
            //static constexpr di order=DEorder;
            di logSize=0;
            d::compact::coord<T, 2> d[DEorder];
            double existence=1;
            //d::compact::coord<T> &pos=d[0], &vel=d[1], &acc=d[2];
            template<typename X, typename...Ts>
                requires std::same_as<d::compact::coord<T, dimension>, typename std::common_type<Ts...>::type> && d::nonDim<X>
                mono(double exist, X it, Ts...args): t(it), existence(exist) {
                    static_assert(sizeof...(Ts)<=DEorder, "d::dyn::mono initialization error, too many arguments");
                    di i=0;
                    (...,void(d[(i++)]=args)); // https://stackoverflow.com/a/34569679/8460574
                    // **This is unsure if it is compact**
                }
            template<typename...Ts>
                requires std::same_as<d::compact::coord<T>, typename std::common_type<Ts...>::type>
                mono(Ts...args): mono(1.0, 0.0, args...) {}
            template<typename...Ts>
                requires std::same_as<d::compact::coord<T>, typename std::common_type<Ts...>::type>
                mono(double exist, Ts...args): mono(exist, 0.0, args...) {}
            template<typename X, typename...Ts> 
                requires std::same_as<d::compact::coord<T>, typename std::common_type<Ts...>::type> && std::signed_integral<X>
                mono(X it, Ts...args): mono(1.0, it, args...) {}
            mono(): mono(1.0, 0.0, d::compact::coord<T, dimension>((T)0)) {}
            inline mono& rmLog() {
                if(log!=nullptr)
                    for(di i=0; i<=logSize; ++i)
                        (log+i)->~mono();
                free(log);
                log=nullptr;
                return *this;
            }
            ~mono() {
                this->rmLog();
            }
            mono(const mono<T, DEorder, dimension, false> &other) {
                for(di i=0; i<DEorder; ++i)
                    d[i]=other.d[i];
            }
            mono(const mono<T, DEorder, dimension, true> &other) {
                for(di i=0; i<DEorder; ++i)
                    d[i]=other.d[i];
            }
            mono(mono<T, logIncrPromise> &&other) noexcept: d(std::exchange(other.d, nullptr)), t(std::exchange(other.t, 0)), log(std::exchange(other.log, nullptr)) {
            }
            mono& operator=(const mono<T, DEorder, dimension, false> &other) {
                if(this==&other) return *this;
                // Basically we aren't replacing logs
                // Only copying t, pos, vel
                this->t=other.t; // As DEorder in array are only relative to the log[0]
                for(di i=0; i<DEorder; ++i)
                    d[i]=other.d[i];
                return *this;
            }
            mono& operator=(const mono<T, DEorder, dimension, true> &other) {
                if(this==&other) return *this;
                // Basically we aren't replacing logs
                // Only copying t, pos, vel
                this->t=other.t; // As DEorder in array are only relative to the log[0]
                for(di i=0; i<DEorder; ++i)
                    d[i]=other.d[i];
                return *this;
            }
            mono<T, DEorder, dimension, logIncrPromise>& operator=(mono<T, DEorder, dimension, logIncrPromise> &&other) noexcept {
                if(this==&other) return *this;
                delete[]log;
                t=other.t;
                log=other.log;
                for(di i=0; i<DEorder; ++i)
                    d[i]=other.d[i];
                other.t=0;
                other.log=nullptr;
                return *this;
            }
            d::compact::coord<T, dimension>& operator[](int i) {
                return this->d[i];
            }
            d::compact::coord<T, dimension> operator[](int i) const {
                return this->d[i];
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
            template<long delta=-1, typename...Ts>
                requires std::same_as<d::compact::coord<T, dimension>, typename std::common_type<Ts...>::type>
                mono shift(Ts...args) const {
                    if constexpr(delta==0) {
                        return *this;
                    } else {
                        auto res=(*this);
                        assert(sizeof...(Ts)<=std::abs(delta) && 
                                "Too many arguments in d::dyn::mono::shift<>()");
                        if constexpr(delta>=0) {
                            for(di i=DEorder-1; i>=delta; --i)
                                res.d[i]=d[i-delta];
                            di i=0;
                            (...,void(res.d[i++] = args)); // https://stackoverflow.com/a/34569679/8460574
                            constexpr long mis=(delta)-sizeof...(Ts);
                            if constexpr(mis) {
                                for(;i<delta; ++i)
                                    res.d[i]=d::compact::coord<T, dimension>(res.d->dim);
                            }
                        } else {
                            for(int i=0; i<DEorder+delta; ++i)
                                res.d[i]=d[i-delta];
                            int i=DEorder+delta;  //Sure?
                            (...,void(res.d[i++] = args)); // https://stackoverflow.com/a/34569679/8460574
                            constexpr long mis=(delta*-1)-sizeof...(Ts);
                            if constexpr(mis) {
                                for(;i<DEorder; ++i)
                                    res.d[i]=d::compact::coord<T, dimension>(res.d->dim);
                            }
                        }
                        return res;
                    }
                }
            template<long delta=-1, typename...Fs>
                requires (!(std::same_as<d::compact::coord<T, dimension>, typename std::common_type<Fs...>::type>))
                // Currently we haven't prepare a proper concept for it...
                // It should chekc that all Fs is convertible_to std::function<d::compact::coord<T>(d::mono<T, logIncrPromise>)>
                mono shift(Fs...funcs) const { // lambda function version
                    return shift<delta>(funcs(*this)...);
                }
            template<long delta=-1> mono shift() const { return this->shift<delta>(d::compact::coord<T, dimension>(d->dim)); }
            friend ostream& operator<<(ostream& os, const mono& x) {
                os<<"============\n";
                for(di i=0; i<DEorder; ++i)
                    os<<x.d[i]<<"\n";
                os<<"============";
                return os;
            }
            template<typename X> mono<T, DEorder, dimension, logIncrPromise>& operator*=(const X& r) {
                for(di i=0; i<DEorder; ++i)
                    d[i]*=r;
                return *this;
            }
            template<typename X> mono<T, DEorder, dimension, logIncrPromise>& operator/=(const X& r) {
                for(di i=0; i<DEorder; ++i)
                    d[i]/=r;
                return *this;
            }
            template<bool B> mono<T, DEorder, dimension, logIncrPromise>& operator+=(const mono<T, B>& r) {
                for(di i=0; i<DEorder; ++i)
                    d[i]+=r[i];
                return *this;
            }
            template<bool B> mono<T, DEorder, dimension, logIncrPromise>& operator-=(const mono<T, B>& r) {
                for(di i=0; i<DEorder; --i)
                    d[i]-=r[i];
                return *this;
            }
            template<typename A, di O, di D, bool B, typename X>
                friend mono<A, O, D, B> operator*(mono<A, O, D, B> lhs, const X& r);
            template<typename A, di O, di D, bool B, typename X>
                friend mono<A, O, D, B> operator*(X r, mono<A, O, D, B> lhs);
            template<typename A, di O, di D, bool B, typename X>
                friend mono<A, O, D, B> operator/(mono<A, O, D, B> lhs, const X& r);
            template<typename A, di O, di D, bool B, typename X>
                friend mono<A, O, D, B> operator/(X r, mono<A, O, D, B> lhs);
            template<typename A, di O, di D, bool B, bool C>
                friend mono<A, O, D, B> operator+(mono<A, O, D, B> lhs, const mono<A, O, D, C>& r);
            template<typename A, di O, di D, bool B, bool C>
                friend mono<A, O, D, B> operator-(mono<A, O, D, B> lhs, const mono<A, O, D, C>& r);
            //template<typename C> operator d::d::compact::coord<C>() const { return pos; }
            template<typename C> operator d::compact::coord<C, dimension>() const { return this->d[this->DEorder]; } 
            //            operator mono<T, false>() const {
            //                mono<T, false> res(this->DEorder, this->d->dim);
            //                res.t=this->t; // As DEorder in array are only relative to the log[0]
            //                res.DEorder=this->DEorder;
            //                res.d=(d::compact::coord<T>*)malloc(sizeof(d::compact::coord<T>)*(DEorder));
            //                for(di i=0; i<DEorder; ++i)
            //                    res.d[i]=this->d[i];
            //                return res;
            //            }
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

#include"./mono.tt"
