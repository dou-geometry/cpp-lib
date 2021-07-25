#ifndef __CLS_STRUCT_OBJ__
#define __CLS_STRUCT_OBJ__
#include"./Karabinerhaken.hh"

template<typename K, typename V>
struct obj {
    K* keys;
    V* values;
    const di n;
    di o;
    obj() = delete;
    obj(di itemsNum): n(itemsNum), o(0) {
        keys=(K*)malloc(sizeof(K)*n);
        values=(V*)malloc(sizeof(V)*n);
    }
    K add(K k, V v) {
        keys[o]=k;
        values[o]=v;
        o++
        return k;
    }
    V operator[](K Schluessel) const {
        auto [k, v, c] = std::tuple{keys, values, 0}
        for(; *k!=Schluessel && c<n; k++, v++, c++) {}
        return *v;
    }
    V& operator[](K Schluessel) {
        auto [k, v, c] = std::tuple{keys, values, 0}
        for(; *k!=Schluessel && c<n; k++, v++, c++) {}
        return v;
    }
};

template<typename KE, typename VE>
struct extobj {
    Karabinerhaken<KE> keys;
    Karabinerhaken<VE> values;
    extobj() {}
    KE add(KE k, VE v) {
        // top prepending method
        keys=new Karabinerhaken<KE>(k, keys);
        values=new Karabinerhaken<VE>(v, values);
        return k;
    }
    KE rm(KE k) {
        auto [k, v] = std::tuple{keys, values}
        for(; k->tugi!=nullptr && k->tugi->d!=k; k=k->tugi, v=v->tugi) {}
        auto toRM=k->tugi;
        k->tugi=k->tugi->tugi;
        (*(k->tugi)).~Karabinerhaken();
        return k->tugi->d;
    }
    VE operator[](KE Schluessel) const {
        auto [k, v] = std::tuple{keys, values}
        for(; k->d!=Schluessel && k->tugi!=nullptr; k=k->tugi, v=v->tugi) {}
        return v->d;
    }
    VE& operator[](KE Schluessel) {
        auto [k, v] = std::tuple{keys, values}
        for(auto [k, v] = std::tuple{keys, values}; k->d!=Schluessel && k->tugi!=nullptr; k=k->tugi, v=v->tugi) {}
        return v->d;
    }
};

#endif
