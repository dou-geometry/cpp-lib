#ifndef __FUNC_NUM_INTE__
#define __FUNC_NUM_INTE__
#include"../cls/line.hpp"
#include"../cls/field.hpp"
#include"../cls/cov.hpp"
#include<tuple>
namespace d::numerical {
    const double EPS=1e-24;
    template<typename T> T integrate(const d::line<T>, const field<T>&);
    template<typename T> coord<T> integrateTil(const coord<T>&, const field<T>&, T);
    template<typename T> T integrate(const d::line<T>, const field<T>&, di);
    template<typename T> coord<T> integrateTil(const coord<T>&, const field<T>&, T, di);
    template<typename T> T integrate(const d::line<T>, const field<T>&, di, di);
    template<typename T> coord<T> integrateTil(const coord<T>&, const field<T>&, T, std::tuple, di, di);
    template<typename T> T integrate(const d::line<T>, const field<T>&, std::tuple<di, di>);
    template<typename T> coord<T> integrateTil(const coord<T>&, const field<T>&, T, std::tuple, std::tuple<di, di>);

    template<typename T>
    class dp {
        T odd, even;
        public:
        dp() {};
        T& operator[](int i) {
            return i%2?odd:even;
        }
        T operator[](int i) const {
            return i%2?odd:even;
        }
    }
}
#endif
