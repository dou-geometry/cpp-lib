#pragma once
#include"../cls/Karabinerhaken.hh"
#include"./mono.hh"

template<typename T>
struct sys:d::Karabinerhaken<d::dyn::mono<T>> {
    sys& next() {
    }
}
