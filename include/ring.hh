#pragma once
#include<numeric.hh>
#include<iostream>

namespace d {
    template<auto leng=1., bool ryou=false> // Currently only supports `double`
        requires d::numeric<typename std::decay<decltype(leng)>::type>
    struct ring {
        double d;
        template<typename T> requires std::convertible_to<T, double> ring(T x): d(x) { this->mod(); }
        inline ring& mod() {
            if constexpr(ryou) while(d>leng) d-=leng;
            else while(d>=leng) d-=leng;
            return *this;
        }
        template<typename T> ring& operator+=(T x) {
            d+=x;
            this->mod();
            return *this;
        }
        template<typename T> ring& operator-=(T x) {
            d-=x;
            this->mod();
            return *this;
        }
        template<typename T> ring& operator*=(T x) {
            d*=x;
            this->mod();
            return *this;
        }
        template<typename T> ring& operator/=(T x) {
            d/=x;
            this->mod();
            return *this;
        }
        operator double() { return this->mod()->d; }
        template<typename I> operator I() { return (I)(this->mod()->d); }
        inline friend std::ostream& operator<<(std::ostream& os, const ring& x) { os << x.d; return os; }
        template<auto Nleng=1., bool Nryou=ryou> ring<Nleng, Nryou> mod() {
            return ring<Nleng, Nryou>(this->d);
        }
    };
}
