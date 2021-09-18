#pragma once
#include<coord.hh>
#include<oricoord.hh>
#include<nonDim.hh>
#include<iostream>
#include <type_traits>
#include<cassert>
#include<functional>
#include<Karabinerhaken.hh>
#define di long unsigned int
#define ull unsigned long long int

namespace d {
    struct polarmono { // DEorder=2
        double t=0;
        d::Karabinerhaken<d::polarmono> *karaLog=nullptr;
        di logSize=0;
        d::polarcoord *d=nullptr;
        polarmono(const d::compact::coord<double, 2>&, const d::compact::coord<double, 2>&);
        polarmono(const d::compact::coord<double, 2>& v): polarmono(d::compact::coord<double, 2>(0.), v) {}
        polarmono(): polarmono(d::compact::coord<double, 2>(0.), d::compact::coord<double, 2>(0.)) {}
        ~polarmono();
        polarmono(const polarmono&);
        polarmono(polarmono&&) noexcept;
        polarmono& operator=(const polarmono&);
        polarmono& operator=(polarmono&&) noexcept;
        inline d::compact::coord<double, 2>& posi() { return d[0]; }
        inline d::compact::coord<double, 2> posi() const { return d[0]; }
        polarmono& operator*=(double r);
        polarmono& operator/=(double r);
        polarmono& operator+=(const polarmono&);
        polarmono& operator-=(const polarmono&);
        friend polarmono& operator+(polarmono, const polarmono&);
        friend polarmono& operator-(polarmono, const polarmono&);
        friend std::ostream& operator<<(std::ostream&, const polarmono&);
        d::polarcoord& operator[](int);
        d::polarcoord operator[](int) const;
        di size() const { return 2; }
    };
}
