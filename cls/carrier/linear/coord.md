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

## `operator=`
```cpp
coord& operator=(const coord<T> &other)
coord& operator=(coord<T> &&other) noexcept
```

## Arithmetic
```cpp
coord<T>& operator-=(const coord<T> &r)
coord<T>& operator*=(const T &r)
coord<T>& operator/=(const T &r)
coord<T>& operator*=(const coord<T> &rhs)
```
```cpp
friend coord<T> operator+(coord<T> lhs, const coord<T> &r)
friend coord<T> operator-(coord<T> lhs, const coord<T> &r)
friend coord<T> operator*(coord<T> lhs, const T &r)
friend coord<T> operator/(coord<T> lhs, const T &r)
```

## `operator[]`
```cpp
T& operator[](int i)
T operator[](int i) const
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
# I/O
```cpp
friend ostream& operator<<(ostream& os, const coord<T> &crd)
void print(int precision=15)
void input()
static void input(coord<T> &x)
```
