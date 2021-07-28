#pragma once
#include<concepts>

namespace d {
    template<typename T>
        requires std::integral<T> || std::floating_point<T> || std::boolean-testable<T>
    struct suu {
        bool hoka=false;
        T d;
        suu(): d(0.) {}
        suu(bool h, T x=0.): hoka(h), d(x) {}
        operator T() { return hoka?d:0; }
    };
}
