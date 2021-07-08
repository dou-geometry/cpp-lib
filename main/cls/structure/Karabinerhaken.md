# Data Structure
```cpp
template<typename C>
struct Karabinerhaken {
    Karabinerhaken* tugi=nullptr;
    C d;
}
```

# Constructor
```cpp
Karabinerhaken(C x, Karabinerhaken* n=nullptr): d(x), tugi(n) {}
```

# Functions

## Connection

Since Karabinerhaken is a one-way list, we only support `insertAfter`.
```cpp
void insertAfter(Karabinerhaken* mae)
void insert(Karabinerhaken* mae)
```
Usage: `(thing you wanna insert).insertAfter(the previous item)`

Sidenote: `insert(Karabinerhaken*)` is an abbr. function for `insertAfter`, to acheive insertion you'll have to pass in 2 `Karabinerhaken*`.

## Insertion

The member function `Karabinerhaken::insert` is a more robust function than `Karabinerhaken::insertAfter`. The function will auto determine the given two point which is first and which is later, and it'll insert the element between them while maintaining the one-way linked-list structure.
```cpp
void insert(Karabinerhaken* ptr1, Karabinerhaken* ptr2)
```

Sidenote: `insert(Karabinerhaken*)` is an abbr. function for `insertAfter`, to acheive insertion you'll have to pass in 2 `Karabinerhaken*`.
