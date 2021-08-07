#ifndef __CLS_STRUCT_OBJ__
#define __CLS_STRUCT_OBJ__
#include<cassert>
#include"./Karabinerhaken.hh"

namespace d::compact {
template<typename K, typename V, di size, bool keyIncrPromise = false>
struct obj {
    K* keys;
    V* values;
    di occupied;
    obj(): occupied(0) {
        keys=(K*)malloc(sizeof(K)*size);
        values=(V*)malloc(sizeof(V)*size);
    }
    K append(K k, V v) {
        assert(occupied<size && "Exceeding d::compact::obj size");
        keys[occupied]=k;
        values[occupied]=v;
        occupied++;
        return k;
    }
    K add(K k, V v) {
        if constexpr(keyIncrPromise) { // Smart insertion that maintains promise
        } else {
            return this->append(k, v);
        }
    }
    V operator()(K Schluessel) const { 
        if constexpr(keyIncrPromise) {// binary search implementation
        } else { // implement middle value guessing
        }
    }
    V operator[](K Schluessel) const {
        auto [k, v, c] = std::tuple{keys, values, 0};
        for(; *k!=Schluessel && c<size; k++, v++, c++) {}
        return *v;
    }
    V& operator[](K Schluessel) {
        auto [k, v, c] = std::tuple{keys, values, 0};
        for(; *k!=Schluessel && c<size; k++, v++, c++) {}
        return v;
    }
};
}

namespace d {
template<typename KE, typename VE>
struct obj {
    Karabinerhaken<KE>* keys;
    Karabinerhaken<VE>* values;
    obj(): keys(new Karabinerhaken<KE>()), values(new Karabinerhaken<VE>()) {}
    KE add(KE k, VE v) {
        // top prepending method
        keys=new Karabinerhaken<KE>(k, keys);
        values=new Karabinerhaken<VE>(v, values);
        return k;
    }
    KE rm(KE sk) {
        auto [k, v] = std::tuple{keys, values};
        for(; k->tugi!=nullptr && k->tugi->d!=sk; k=k->tugi, v=v->tugi) {}
        auto toRM=k->tugi;
        k->tugi=k->tugi->tugi;
        (*(k->tugi)).~Karabinerhaken();
        return k->tugi->d;
    }
    VE operator[](KE Schluessel) const {
        auto [k, v] = std::tuple{keys, values};
        for(; k->d!=Schluessel && k->tugi!=nullptr; k=k->tugi, v=v->tugi) {}
        return v->d;
    }
    VE& operator[](KE Schluessel) {
        auto [k, v] = std::tuple{keys, values};
        for(auto [k, v] = std::tuple{keys, values}; k->d!=Schluessel && k->tugi!=nullptr; k=k->tugi, v=v->tugi) {}
        return v->d;
    }
    VE operator()(KE Schluessel) const {
        // unable to implement binary search
        return values->d;
    }
};
}

#endif
