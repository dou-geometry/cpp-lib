#pragma once
#include<concepts>

namespace d {
template<typename R>
concept tracksTime = requires(const R &r) { r.t; };
}
