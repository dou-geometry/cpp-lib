# Data Structure

```cpp
template<typename T>
struct coord {
    T *d;
    di dim;
};
```

#Constructor
```cpp
coord(di dim, T val=0.0)
coord(double r, deg theta, deg phi, double divisor=1.0)
coord(double r, deg theta, double divisor=1.0)
coord(initializer_list<T> l)
coord(): coord(2, (T)0)
coord(const coord<T> &other)
coord(coord<T> &&other) noexcept
```

# Operator

## `=`
```cpp
coord& operator=(const coord<T> &other)
coord& operator=(coord<T> &&other) noexcept
```

# Functions
```cpp
double norm() const
double norm2() const
coord<T> unit() const
coord<ll> round() const
coord<ll> rupper() const
coord<double> round(int digits=0) const
coord<T> abs() const
coord<ull> unsign() const
T dot(coord<T> &r) const
```
