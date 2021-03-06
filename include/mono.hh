#ifndef __CAR_LINEAR_MONO_HPP__
#define __CAR_LINEAR_MONO_HPP__
#include<coord.hh>
#include<nonDim.hh>
#include<iostream>
#include <type_traits>
#include<cassert>
#include<functional>
#include<Karabinerhaken.hh>
#define di long unsigned int
#define ull unsigned long long int
namespace d {
    template<typename G>
        struct mono {
            coord<G> x, v;
            mono(): mono(2) {}
            mono(di dim): x(dim), v(dim) {}
            mono(coord<G> pos, coord<G> vel): x(pos), v(vel) {}
            friend std::ostream& operator<<(std::ostream& os, mono& a) {
                os << "x="<<a.x<<"; v="<<a.v;
                return os;
            }
        };
}




namespace d::dyn {
    template<typename T, bool logIncrPromise=false>
        struct mono {
            di order;
            double t=0;
            mono* log=nullptr;
            di logSize=0;
            d::coord<T> *d=nullptr;
            //d::coord<T> &pos=d[0], &vel=d[1], &acc=d[2];
            template<typename X, typename...Ts>
                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type> && d::nonDim<X>
                mono(di ord, X it, Ts...args): order(ord), t(it) {
                    d=(d::coord<T>*)malloc(sizeof(d::coord<T>)*(order));
                    assert(d!=NULL);
                    assert(sizeof...(Ts)<=(order)&& "d::dyn::mono initialization error, too many arguments");
                    di i=0;
                    (...,void(new(d+(i++))d::coord<T>(args))); // https://stackoverflow.com/a/34569679/8460574
                    //std::cout << "Size: " << sizeof...(Ts) << std::endl;
                    //for(; i<order; ++i)
                    for(i=sizeof...(Ts); i<order; ++i)
                        new(d+i)d::coord<T>(d->dim);
                }
            template<typename...Ts>
                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type>
                mono(Ts...args): mono(sizeof...(Ts), 0.0, args...) {}
            template<typename...Ts> 
                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type>
                mono(di ord, Ts...args): mono(ord, 0.0, args...) {}
            template<typename X, typename...Ts> 
                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type> && d::nonDim<X>
                mono(X it, Ts...args): mono(sizeof...(Ts), it, args...) {}
            template<typename X, typename...Ts> 
                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type> && d::nonDim<X>
                mono(X it, di ord, Ts...args): mono(ord, it, args...) {}
            mono(): mono(1ul, 0.0, d::coord<T>(1)) {}
            mono(di EQorder, di dimension=1): mono(EQorder, 0.0, d::coord<T>(dimension)) {}
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
                if (d!=nullptr)
                    for(di i=0; i<order; i++)
                        (d+i)->~coord();
                // this supposed, as all existing constructors behaves,
                // you couldn't create a d::dyn::mono without fully initializing the d::dyn:::mono::d
                // use malloc is just saving time as it doesn't require constructor to be called twice
                free(d);
            }
            mono(const mono<T, false> &other): order(other.order), t(other.t) {
                d::coord<T>* tptr=(d::coord<T>*)malloc(sizeof(d::coord<T>)*(order));
                assert(tptr!=NULL);
                d=tptr;
                for(di i=0; i<order; ++i)
                    new(d+i)d::coord<T>(other.d[i]);
            }
            mono(const mono<T, true> &other): order(other.order), t(other.t) {
                d::coord<T>* tptr=(d::coord<T>*)malloc(sizeof(d::coord<T>)*(order));
                assert(tptr!=NULL);
                d=tptr;
                for(di i=0; i<order; ++i)
                    new(d+i)d::coord<T>(other.d[i]);
                //d[i]=other.d[i];
            }
            mono(mono<T, logIncrPromise> &&other) noexcept: d(std::exchange(other.d, nullptr)), order(std::exchange(other.order, 0)), t(std::exchange(other.t, 0)), log(std::exchange(other.log, nullptr)) {
            }
            mono& operator=(const mono<T, false> &other) requires (!logIncrPromise) {
                if(this==&other) return *this;
                // Basically we aren't replacing logs
                // Only copying t, pos, vel
                this->t=other.t; // As order in array are only relative to the log[0]
                this->order=other.order;
                d::coord<T>* tptr=(d::coord<T>*)malloc(sizeof(d::coord<T>)*(order));
                assert(tptr!=NULL);
                if(d!=nullptr)
                    for(di i=0; i<order; i++)
                        (d+i)->~coord();
                d=tptr;
                for(di i=0; i<order; ++i)
                    new(d+i)d::coord<T>(other.d[i]);
                return *this;
            }
            mono& operator=(const mono<T, true> &other) {
                if constexpr(logIncrPromise) if(this==&other) return *this;
                // Basically we aren't replacing logs
                // Only copying t, pos, vel
                this->t=other.t; // As order in array are only relative to the log[0]
                this->order=other.order;
                d::coord<T>* tptr=(d::coord<T>*)malloc(sizeof(d::coord<T>)*(order));
                assert(tptr!=NULL);
                if(d!=nullptr)
                    for(di i=0; i<order; i++)
                        d[i].~coord();
                free(d);
                d=tptr;
                for(di i=0; i<order; ++i)
                    new(d+i)d::coord<T>(other.d[i]);
                return *this;
            }
            mono<T, logIncrPromise>& operator=(mono<T, logIncrPromise> &&other) noexcept {
                if(this==&other) return *this;
                delete[]log;
                if(d!=nullptr)
                    for(di i=0; i<order; i++)
                        d[i].~coord();
                free(d);
                order=other.order;
                t=other.t;
                log=other.log;
                d=other.d;
                other.order=0;
                other.t=0;
                other.log=nullptr;
                other.d=nullptr;
                return *this;
            }
            d::coord<T>& operator[](int i) {
                return this->d[i];
            }
            d::coord<T> operator[](int i) const {
                return this->d[i];
            }
            mono& operator()(double st) { // This preforms check if t matches, if failed it'll be followed by binary search
                double dt=this->log[1].t-(this->log[0].t);
                st-=this->log[0].t;
                int id=st/dt;
                if constexpr(logIncrPromise) { return this->log[id]; }
                else {
                    if((this->log[id]).t==st) {
                        return this->log[id];
                    } else {
                        while((this->log[id]).t!=st) {
                            id-=((this->log[id]).t)>st?id/2:-1;
                        }
                        return this->log[id];
                    }
                }
            }
            template<long delta=-1, typename...Ts>
                requires std::same_as<d::coord<T>, typename std::common_type<Ts...>::type>
                mono shift(Ts...args) const {
                    if constexpr(delta==0) {
                        return *this;
                    } else {
                        auto res=(*this);
                        assert(sizeof...(Ts)<=std::abs(delta) && 
                                "Too many arguments in d::dyn::mono::shift<>()");
                        if constexpr(delta>=0) {
                            for(di i=order-1; i>=delta; --i)
                                res.d[i]=d[i-delta];
                            di i=0;
                            (...,void(res.d[i++] = args)); // https://stackoverflow.com/a/34569679/8460574
                            constexpr long mis=(delta)-sizeof...(Ts);
                            if constexpr(mis) {
                                for(;i<delta; ++i)
                                    res.d[i]=d::coord<T>(res.d->dim);
                            }
                        } else {
                            for(int i=0; i<order+delta; ++i)
                                res.d[i]=d[i-delta];
                            int i=order+delta;  //Sure?
                            (...,void(res.d[i++] = args)); // https://stackoverflow.com/a/34569679/8460574
                            constexpr long mis=(delta*-1)-sizeof...(Ts);
                            if constexpr(mis) {
                                for(;i<order; ++i)
                                    res.d[i]=d::coord<T>(res.d->dim);
                            }
                        }
                        return res;
                    }
                }
            template<long delta=-1, typename...Fs>
                requires (!(std::same_as<d::coord<T>, typename std::common_type<Fs...>::type>))
                // Currently we haven't prepare a proper concept for it...
                // It should chekc that all Fs is convertible_to std::function<d::coord<T>(d::mono<T, logIncrPromise>)>
                mono shift(Fs...funcs) const { // lambda function version
                    return shift<delta>(funcs(*this)...);
                }
            template<long delta=-1> mono shift() const { return this->shift<delta>(d::coord<T>(d->dim)); }
            friend std::ostream& operator<<(std::ostream& os, const mono& x) {
                os<<"============\n";
                for(di i=0; i<x.order; ++i)
                    os<<x.d[i]<<"\n";
                os<<"============";
                return os;
            }
            template<typename X> mono<T, logIncrPromise>& operator*=(const X& r) {
                for(di i=0; i<order; ++i)
                    d[i]*=r;
                return *this;
            }
            template<typename X> mono<T, logIncrPromise>& operator/=(const X& r) {
                for(di i=0; i<order; ++i)
                    d[i]/=r;
                return *this;
            }
            template<bool B> mono<T, logIncrPromise>& operator+=(const mono<T, B>& r) {
                for(di i=0; i<order; ++i)
                    d[i]+=r[i];
                return *this;
            }
            template<bool B> mono<T, logIncrPromise>& operator-=(const mono<T, B>& r) {
                for(di i=0; i<order; --i)
                    d[i]-=r[i];
                return *this;
            }
            template<typename A, bool B, typename X>
                friend mono<A, B> operator*(mono<A, B> lhs, const X& r);
            template<typename A, bool B, typename X>
                friend mono<A, B> operator*(X r, mono<A, B> lhs);
            template<typename A, bool B, typename X>
                friend mono<A, B> operator/(mono<A, B> lhs, const X& r);
            template<typename A, bool B, typename X>
                friend mono<A, B> operator/(X r, mono<A, B> lhs);
            template<typename A, bool B, bool C>
                friend mono<A, B> operator+(mono<A, B> lhs, const mono<A, C>& r);
            template<typename A, bool B, bool C>
                friend mono<A, B> operator-(mono<A, B> lhs, const mono<A, C>& r);
            //template<typename C> operator d::d::coord<C>() const { return pos; }
            template<typename C> operator d::coord<C>() const { return this->d[this->order]; } 
            //            operator mono<T, false>() const {
            //                mono<T, false> res(this->order, this->d->dim);
            //                res.t=this->t; // As order in array are only relative to the log[0]
            //                res.order=this->order;
            //                res.d=(d::coord<T>*)malloc(sizeof(d::coord<T>)*(order));
            //                for(di i=0; i<order; ++i)
            //                    res.d[i]=this->d[i];
            //                return res;
            //            }
            di size() const { return order; }
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


namespace d::dyn::compact {
    template<typename T, di DEorder=2, di dimension=2, bool logIncrPromise=false>
        struct mono {
            double t=0;
            mono<T, DEorder, dimension, logIncrPromise>* log=nullptr;
            static constexpr di order=DEorder;
            di logSize=0;
            d::compact::coord<T, dimension> d[DEorder];
            //d::coord<T> &pos=d[0], &vel=d[1], &acc=d[2];
            template<typename X, typename...Ts>
                requires std::same_as<d::compact::coord<T, dimension>, typename std::common_type<Ts...>::type> && d::nonDim<X>
                mono(X it, Ts...args): t(it) {
                    static_assert(sizeof...(Ts)<=DEorder, "d::dyn::mono initialization error, too many arguments");
                    di i=0;
                    (...,(void)(d[(i++)]=args)); // https://stackoverflow.com/a/34569679/8460574
                    // **This is unsure if it is compact**
                }
            template<typename...Ts>
                requires std::same_as<d::compact::coord<T, dimension>, typename std::common_type<Ts...>::type>
                mono(Ts...args): mono(0.0, args...) {}
            mono(): mono(0.0, d::compact::coord<T, dimension>(0)) {}
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
                t=other.t;
                for(di i=0; i<DEorder; ++i)
                    d[i]=other.d[i];
            }
            mono(const mono<T, DEorder, dimension, true> &other) {
                t=other.t;
                for(di i=0; i<DEorder; ++i)
                    d[i]=other.d[i];
            }
            mono(mono<T, DEorder, dimension, logIncrPromise> &&other) noexcept: t(std::exchange(other.t, 0)), log(std::exchange(other.log, nullptr)) {
                std::swap(d, other.d);
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
            mono& operator()(double st) { // This preforms check if t matches, if failed it'll be followed by binary search
                double dt=this->log[1]-(this->log[0]);
                st-=this->log[0];
                int id=st/dt;
                if constexpr(logIncrPromise) { return this->log[id]; }
                else {
                    if((this->log[id]).t==st) {
                        return this->log[id];
                    } else {
                        while((this->log[id]).t!=st) {
                            id-=((this->log[id]).t)>st?id/2:-1;
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
                                    res.d[i]=d::coord<T>(res.d->dim);
                            }
                        } else {
                            for(int i=0; i<DEorder+delta; ++i)
                                res.d[i]=d[i-delta];
                            int i=DEorder+delta;  //Sure?
                            (...,void(res.d[i++] = args)); // https://stackoverflow.com/a/34569679/8460574
                            constexpr long mis=(delta*-1)-sizeof...(Ts);
                            if constexpr(mis) {
                                for(;i<DEorder; ++i)
                                    res.d[i]=d::coord<T>(res.d->dim);
                            }
                        }
                        return res;
                    }
                }
            template<long delta=-1, typename...Fs>
                requires (!(std::same_as<d::compact::coord<T, dimension>, typename std::common_type<Fs...>::type>))
                // Currently we haven't prepare a proper concept for it...
                // It should chekc that all Fs is convertible_to std::function<d::coord<T>(d::mono<T, logIncrPromise>)>
                mono shift(Fs...funcs) const { // lambda function version
                    return shift<delta>(funcs(*this)...);
                }
            template<long delta=-1> mono shift() const { return this->shift<delta>(d::compact::coord<T, dimension>(d->dim)); }
            friend std::ostream& operator<<(std::ostream& os, const mono& x) requires(DEorder==1) {
                os << "x="<<x.d[0];
                return os;
            }
            friend std::ostream& operator<<(std::ostream& os, const mono& x) requires(DEorder==2) {
                os << "x="<<x.d[0]<<", v="<<x.d[1];
                return os;
            }
            friend std::ostream& operator<<(std::ostream& os, const mono& x) requires(DEorder==3) {
                os << "x="<<x.d[0]<<", v="<<x.d[1]<<", a="<<x.d[2];
                return os;
            }
            friend std::ostream& operator<<(std::ostream& os, const mono& x) requires(DEorder>3) {
                os<<"============\n";
                for(di i=0; i<x.order; ++i)
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
            template<bool B> mono<T, DEorder, dimension, logIncrPromise>& operator+=(const mono<T, DEorder, dimension, B>& r) {
                for(di i=0; i<DEorder; ++i)
                    d[i]+=r[i];
                return *this;
            }
            template<bool B> mono<T, DEorder, dimension, logIncrPromise>& operator-=(const mono<T, DEorder, dimension, B>& r) {
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
            //template<typename C> operator d::d::coord<C>() const { return pos; }
            template<typename C> operator d::compact::coord<C, dimension>() const { return this->d[this->DEorder]; } 
            //            operator mono<T, false>() const {
            //                mono<T, false> res(this->DEorder, this->d->dim);
            //                res.t=this->t; // As DEorder in array are only relative to the log[0]
            //                res.DEorder=this->DEorder;
            //                res.d=(d::coord<T>*)malloc(sizeof(d::coord<T>)*(DEorder));
            //                for(di i=0; i<DEorder; ++i)
            //                    res.d[i]=this->d[i];
            //                return res;
            //            }
            di size() const { return DEorder; }
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
            mono& operator()(double st) { // This preforms check if t matches, if failed it'll be followed by binary search
                double dt=this->log[1]-(this->log[0]);
                st-=this->log[0];
                int id=st/dt;
                if constexpr(logIncrPromise) { return this->log[id]; }
                else {
                    if((this->log[id]).t==st) {
                        return this->log[id];
                    } else {
                        while((this->log[id]).t!=st) {
                            id-=((this->log[id]).t)>st?id/2:-1;
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
            friend std::ostream& operator<<(std::ostream& os, const mono& x) {
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


namespace d::compact {
    template<di dimension=2>
        struct mono:d::dyn::compact::mono<double, 2, dimension, true> {
            using parent=d::dyn::compact::mono<double, 2, dimension, true>;
            using parent::d;
            mono(mono<dimension> &&other) noexcept: karaLog(std::exchange(other.karaLog, nullptr)), parent(other) {}
            mono& operator=(mono<dimension> &&other) noexcept {
                if(this==&other) return *this;
                delete karaLog;
                karaLog=std::exchange(other.karaLog, nullptr);
                parent::operator=(other);
                return *this;
            }
            using parent::mono;
            //using parent::mono;
            d::Karabinerhaken<d::compact::mono<dimension>> *karaLog=nullptr;
            ~mono() {
                //std::cout << karaLog << std::endl;
                delete karaLog;
            }
            mono(const mono<dimension> &other): parent(other) {}
            mono& operator=(const mono<dimension> &other) {
                parent::operator=(other);
            }
            d::compact::coord<double, dimension>& posi() { return d[0]; }
            d::compact::coord<double, dimension> posi() const { return d[0]; }
        };
}


#include"./mono.tt"

#endif
