#pragma once
#include"../concepts/numeric.hh"

namespace d {
    template<auto leng>
        requires d::numeric<typename std::decay<decltype(leng)>::type>
    struct ring {
    }
}
