# ToC

- [`compact/`](./compact), a version of the classes in this directory, but uses standard array instead of VLA.

```cpp
// structure
// structure/chain.hpp
template<typename C>
struct Karabinerhaken {
    Karabinerhaken* tugi=nullptr;
    C d;
};
// structure/field.hpp
template<typename H>
struct field {
    H* d;
    ull border;
    ull* sL;
    unsigned short multiplier=1;
    coord<ll> *baseCrd;
};
struct cov:field<bool> {
    di resolution=1;
};
// structure/line.hpp
template<typename L>
struct L {
    coord<L> s, t, d;
};
// carrier
// carrier/linear.hpp
template<typename T>
struct coord {
    T *d;
    di dim;
};
template<typename M>
struct matrix {
    M** d;
    di x, y;
};
```
