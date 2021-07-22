#pragma once
#include<concepts>

template<typename R>
concept tracksTime = requires(const R &r) { r.t; };
