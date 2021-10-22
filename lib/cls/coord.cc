#include<coord.hh>

template struct d::coord<int>;
template struct d::coord<unsigned int>;
template struct d::coord<unsigned long long int>;
template struct d::coord<double>;
template struct d::coord<long double>;

template struct d::compact::coord<double, 1>;
template struct d::compact::coord<double, 2>;
template struct d::compact::coord<double, 3>;
template struct d::compact::coord<double, 4>;

template struct d::compact::coord<long double, 1>;
template struct d::compact::coord<long double, 2>;
template struct d::compact::coord<long double, 3>;
template struct d::compact::coord<long double, 4>;

/*
template struct d::compact::coord<int, 1>;
template struct d::compact::coord<int, 2>;
template struct d::compact::coord<int, 3>;
template struct d::compact::coord<int, 4>;
*/
