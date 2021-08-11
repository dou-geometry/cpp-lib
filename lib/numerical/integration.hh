#ifndef __FUNC_NUM_INTE__
#define __FUNC_NUM_INTE__
#include"../cls.hh"
#include"../cls/line.hh"
#include"../cls/field.hh"
#include"../cls/cov.hh"
#define di long unsigned int
#define ull unsigned long long int
#define ll long long int
#include<tuple>
#include<iostream>
namespace d::numerical {
    const double EPS=1e-12;
    // Function Integration
    template<typename T, typename L> T integrate(const d::line<T>&, const L&);
    // Field integration
    template<typename T> T integrate(const d::line<T>, const field<T>&);
    template<typename T> d::coord<T> integrateTil(const d::coord<T>&, const field<T>&, T);
    template<typename T> T integrate(const d::line<T>, const field<T>&, di);
    template<typename T> d::coord<T> integrateTil(const d::coord<T>&, const field<T>&, T, di);
    template<typename T> T integrate(const d::line<T>, const field<T>&, di, di);
    template<typename T> d::coord<T> integrateTil(const d::coord<T>&, const field<T>&, T, di, di);
    template<typename T> T integrate(const d::line<T>, const field<T>&, std::tuple<di, di>);
    template<typename T> d::coord<T> integrateTil(const d::coord<T>&, const field<T>&, T, std::tuple<di, di>);

    template<typename T>
    class dp {
        T odd, even;
        public:
        T& operator[](int i) {
            return i%2?odd:even;
        }
        T operator[](int i) const {
            return i%2?odd:even;
        }
        friend std::ostream& operator<<(std::ostream& os, dp<T>& x) {
            os << "Odd: " << x.odd << ", Even: " << x.even;
            return os;
        }
    };
}
#endif
