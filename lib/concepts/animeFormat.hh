#pragma once
#include<string>

template<std::string T>
concept animeFormat = T=="gif" || T=="apng";
