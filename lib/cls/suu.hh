#pragma once
#include<concepts>

namespace std {
  template<class B>
  concept boolean =
    movable<remove_cvref_t<B>> &&
    requires(const remove_reference_t<B>& b1,
             const remove_reference_t<B>& b2, const bool a) {
      { b1 } -> convertible_to<bool>;
      { !b1 } -> convertible_to<bool>;
      { b1 && b2 } -> same_as<bool>;
      { b1 &&  a } -> same_as<bool>;
      {  a && b2 } -> same_as<bool>;
      { b1 || b2 } -> same_as<bool>;
      { b1 ||  a } -> same_as<bool>;
      {  a || b2 } -> same_as<bool>;
      { b1 == b2 } -> convertible_to<bool>;
      { b1 ==  a } -> convertible_to<bool>;
      {  a == b2 } -> convertible_to<bool>;
      { b1 != b2 } -> convertible_to<bool>;
      { b1 !=  a } -> convertible_to<bool>;
      {  a != b2 } -> convertible_to<bool>;
    };
}

namespace d {
    template<typename T>
        requires std::integral<T> || std::floating_point<T> || std::boolean<T>
    struct suu {
        bool hoka=false;
        T d;
        suu(): d(0.) {}
        suu(bool h, T x=0.): hoka(h), d(x) {}
        operator T() { return hoka?d:0; }
    };
}
