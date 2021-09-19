#pragma once

namespace d {
    struct rad {
        double val;
        rad(): val(0) {}
        rad(double x): val(x) {}
        operator double() const {
            return val;
        }
    };
    struct deg {
        double val;
        rad d;
        deg(d::rad x): d(x), val(x/M_PI*180.) {}
        deg(double x): val(x), d(x/180.*M_PI) {}
        // Remember all function using d::deg should be marked as explicit,
        // otherwise above constructor should be comment out to prevent direct casting,
        // instead use below constructor.
        deg(int whole, int decimal=0) {
            val=whole;
            int digits=0;
            for(; decimal/(std::pow(10, digits))!=0; ++digits) {};
            std::cout << "Digits: "<<digits<<std::endl;
            val+=decimal/std::pow(10, digits);
            d=val/180.*M_PI;
        }
        deg(): val(0), d(0) {}
        ~deg() = default;
        operator d::rad() const {
            return d;
        }
        operator double() const {
            return (double)d;
        }
    };
    struct trig {
        double val;
    };
    struct jigen {
        di val;
    };
}