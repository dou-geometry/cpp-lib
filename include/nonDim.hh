# pragma once
#include<concepts>
namespace d {

template<typename T>
concept nonDim = std::floating_point<T> || std::signed_integral<T>;

}
