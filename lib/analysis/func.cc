#include"../numerical/func.hh"

namespace d::numerical::corrfunc {
    template float linear(const func<float>&, const coord<float>&);
    template double linear(const func<double>&, const coord<double>&);
    template long double linear(const func<long double>&, const coord<long double>&);
    template __float128 linear(const func<__float128>&, const coord<__float128>&);
}
