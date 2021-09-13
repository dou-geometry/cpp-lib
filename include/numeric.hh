#pragma once
#include<concepts>

namespace d {
    template<typename T>
        concept numeric = std::integral<T> || std::floating_point<T>;
}
