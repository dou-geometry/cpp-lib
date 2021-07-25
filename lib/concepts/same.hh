#pragma once
#include<concepts>
namespace d::concepts {
    template<typename A, typename B>
        concept sameThing = requires(A& a, B& b) {
            std::is_same<A, B> &&
                a.dim==b.dim;
        };
}
