#pragma once
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
        polarmono(const d::polarcoord&, const d::polarcoord&);
        polarmono(const d::polarcoord& v): polarmono(d::polarcoord(0.), v) {}
        polarmono(): polarmono(d::polarcoord(0.), d::polarcoord(0.)) {}
        ~polarmono();
        polarmono(const polarmono&);
        polarmono(polarmono&&) noexcept;
        polarmono& operator=(const polarmono&);
        polarmono& operator=(polarmono&&) noexcept;
        inline d::polarcoord& posi() { return d[0]; }
        inline d::polarcoord posi() const { return d[0]; }
        polarmono& operator*=(double r);
        polarmono& operator/=(double r);
        polarmono& operator+=(const polarmono&);
        polarmono& operator-=(const polarmono&);
        friend polarmono& operator+(polarmono, const polarmono&);
        friend polarmono& operator-(polarmono, const polarmono&);
        d::polarcoord& operator[](int);
        d::polarcoord operator[](int) const;
        friend std::ostream& operator<<(std::ostream&, const polarmono&);
        di size() const { return 2; }
    };
}
