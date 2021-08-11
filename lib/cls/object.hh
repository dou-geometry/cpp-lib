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
    friend std::ostream& operator<<(std::ostream& os, const obj& x)
        requires std::convertible_to<K, double> && std::convertible_to<V, double> {
            for(di i=0; i<size; ++i)
                os << "("<<x.keys[i]<<", "<<x.values[i]<<")\n";
            return os;
        }
};
}

namespace d {
template<typename KE, typename VE>
struct obj {
    Karabinerhaken<KE>* keys;
    Karabinerhaken<VE>* values;
    obj(): keys(new Karabinerhaken<KE>()), values(new Karabinerhaken<VE>()) {}
    KE append(KE k, VE v) {
        // tail appending method
        keys->last()->tugi=new Karabinerhaken<KE>(k);
        values->last()->tugi=new Karabinerhaken<VE>(v);
        return k;
    }
    KE add(KE k, VE v) { return this->append(k, v); }
    KE prepend(KE k, VE v) {
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
    friend std::ostream& operator<<(std::ostream& os, const obj& x)
        requires std::convertible_to<KE, double> && std::convertible_to<VE, double> {
            for(di i=0; i<x.keys.size(); ++i)
                os << "("<<x.keys->after(i)<<", "<<x.values->after(i)<<")\n";
            return os;
        }
};
}

namespace d {
template<typename KE, typename VE>
struct prependObj {
    Karabinerhaken<KE>* keys;
    Karabinerhaken<VE>* values;
    prependObj(): keys(new Karabinerhaken<KE>()), values(new Karabinerhaken<VE>()) {}
    KE add(KE k, VE v) {
        // top prepending method (fast insertion)
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
    friend std::ostream& operator<<(std::ostream& os, const prependObj& x)
        requires std::convertible_to<KE, double> && std::convertible_to<VE, double> {
            for(di i=0; i<x.keys->size(); ++i)
                os << "("<<x.keys->after(i)<<", "<<x.values->after(i)<<")\n";
            return os;
        }
};
}

namespace d {
template<typename KE, typename VE>
    requires d::nonDim<KE>
struct objfast {
    Karabinerhaken<KE>* keys;
    Karabinerhaken<VE>* values;
    di occupied=0;
    objfast(): keys(new Karabinerhaken<KE>()), values(new Karabinerhaken<VE>()) {}
    KE add(KE k, VE v) {
        // top prepending method (fast insertion)
        keys=new Karabinerhaken<KE>(k, keys);
        values=new Karabinerhaken<VE>(v, values);
        occupied++;
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
    VE operator[](di i) const {
        return keys->after(occupied-i);
    }
    VE& operator[](di i) {
        return keys->after(occupied-i);
    }
    VE operator()(KE Schluessel) const {
        // unable to implement binary search
        return values->d;
    }
    friend std::ostream& operator<<(std::ostream& os, const objfast& x)
        requires std::convertible_to<KE, double> && std::convertible_to<VE, double> {
            di i=x.occupied;
            do {
                --i;
                os << "("<<x.keys->after(i)<<", "<<x.values->after(i)<<")\n";
            } while(i!=0);
            return os;
        }
};
}

#endif
