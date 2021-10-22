#pragma once
#include<concepts>

template<typename F, typename T>
concept returnSame = requires(const F& f, const T& t) {
    {f(t)}->std::same_as<T>;
};

template<typename F, typename T>
concept returnSameWithin = requires(const F& f, const T& t) {
    {f(t[0])}->std::same_as<typename std::decay<decltype(t[0])>::type>;
}
