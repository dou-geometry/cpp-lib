#pragma once
#include<concepts>

namespace d {
    template<typename T>
        requires std::integral<T> || std::floating_point<T> || std::boolean-testable<T>
    struct suu {
        bool hoka=false;
        T d;
    };
}
