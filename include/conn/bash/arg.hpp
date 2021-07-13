#ifndef __CONN_BASH_ARG__
#define __CONN_BASH_ARG__
namespace d::conn::bash::arg {
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<concepts>

template<typename O>
struct opt {
    O* ptr;
    char key;
}

struct opts {
    opts() {}
    ~opts() {}
    operator[](char* key) {}
    char*() {
    }
}

template<typename U>
void setup(std::convertible_to<U> auto ...);
void setup();

}
#endif
