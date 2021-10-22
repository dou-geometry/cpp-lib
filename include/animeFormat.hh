#pragma once
#include<string>

namespace d {
template<const char *T>
concept animeFormat = T=="gif" || T=="apng";
}
