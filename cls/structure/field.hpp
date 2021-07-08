#ifndef __STRUCT_FIELD_HPP__
#define __STRUCT_FIELD_HPP__
namespace d{

#include"line.hpp"

template<typename H>
struct field {
    H* d; // [-SL,SL]*[-SL,SL]
    ull border; //max ID
    ull *sL;
    unsigned short multiplier=1;
    coord<long long int> *baseCrd;
    field(coord<long long int> bl, coord<long long int> tr, H val=1) {
        baseCrd=new coord<long long int>(bl.round());
        sL=new ull[(*baseCrd).dim];
        auto tmp=(tr-bl).unsign();
        for(di i=0;i<bl.dim;i++) {
            sL[i]=tmp[i]+1;
        }
        border=coordZuID(tr);
        //init d
        d=new H[border+1];
        // https://stackoverflow.com/a/29977424/8460574
        for(ull i=0;i<=border;i++) d[i]=val;
    }
    field(const coord<long long int> sz,H val=1):field(sz*-1, sz, val){}
    template<typename V>field(const coord<V> sz, H val=1):field(sz.round(), val){}
    template<typename V>field(const coord<V> bl, const coord<V> tr, H val=1):field(bl.round(), tr.round(), val){}
#ifdef __NVCC__
    field<H>* push() {
        field<H> *dest;
        auto cpy=*this;
        auto nB=sizeof(*this);
        gpuErrchk(cudaMalloc((void **) &dest, nB));
        auto oldD=cpy.d;
        auto oldSl=cpy.sL;
        gpuErrchk(cudaMalloc((void **) &(cpy.d), sizeof(H)*(border+1)));
        gpuErrchk(cudaMalloc((void **) &(cpy.sL), sizeof(ull)*((*baseCrd).dim)));
        auto oldCrd=cpy.baseCrd;
        cpy.baseCrd=(*baseCrd).push();
        gpuErrchk(cudaMemcpy(cpy.d, this->d, sizeof(H)*(border+1), cudaMemcpyHostToDevice));
        gpuErrchk(cudaMemcpy(cpy.sL, this->sL, sizeof(ull)*((*baseCrd).dim), cudaMemcpyHostToDevice));
        gpuErrchk(cudaMemcpy(dest, &cpy, nB, cudaMemcpyHostToDevice));
        cpy.d=oldD; cpy.sL=oldSl; cpy.baseCrd=oldCrd;
        return dest;
    }
    field<H>* pull() {
        auto nB=sizeof(*this);
        field<H> *dest=(field<H> *)malloc(nB);
        gpuErrchk(cudaMemcpy(dest, this, nB, cudaMemcpyDeviceToHost));
        //auto dBk=(*dest).d, slBk=(*dest).sL, bcrdBk=(*dest).baseCrd;
        auto oldD=(*dest).d;
        auto oldSl=(*dest).sL;
        (*dest).baseCrd=(*((*dest).baseCrd)).pull();
        (*dest).d=new H[(*dest).border+1];
        (*dest).sL=new ull[(*((*dest).baseCrd)).dim];
        gpuErrchk(cudaMemcpy((*dest).d, oldD, sizeof(H)*((*dest).border+1), cudaMemcpyDeviceToHost));
        gpuErrchk(cudaMemcpy((*dest).sL, oldSl, sizeof(ull)*((*(*dest).baseCrd).dim), cudaMemcpyDeviceToHost));
        return dest;
    }
#endif
    ~field() {
        #ifdef __NVCC__
            #ifdef __CUDA_ARCH__
            free(d);
            free(sL);
            #else
            cudaPointerAttributes attributes;
            gpuErrchk(cudaPointerGetAttributes(&attributes, d));
            if(attributes.type == 0) {
                free(d);
                free(sL);
            } else if(attributes.type==1) {
                free(d);
                free(sL);
            } else if(attributes.type==2) {
                gpuErrchk(cudaFree(d));
                gpuErrchk(cudaFree(sL));
            } else {
                // This is cudaMemoryTypeManaged memory, which no idea what this is...
            }
            #endif
        #else
            delete[]d;
            delete[]sL;
        #endif
        (*baseCrd).~coord();
    }
    field(const field<H> &other): border(other.border) {
        baseCrd=new coord<long long int>(*(other.baseCrd));
        sL=new ull[(*baseCrd).dim];
        for(di i=0;i<(*baseCrd).dim;i++) {
            sL[i]=other.sL[i];
        }
        d=new H[border+1];
        // https://stackoverflow.com/a/29977424/8460574
        for(ull i=0;i<=border;i++) d[i]=other.d[i];
    }
    //field(const field<H> &&other) noexcept: d(std::exchange(other.d, nullptr)), border, sL, baseCrd {}
    field& operator=(const field<H> &other) {
        if (this == &other) return *this;
        baseCrd=new coord<long long int>(*(other.baseCrd));
        sL=new ull[(*baseCrd).dim];
        for(di i=0;i<(*baseCrd).dim;i++) {
            sL[i]=other.sL[i];
        }
        d=new H[border+1];
        // https://stackoverflow.com/a/29977424/8460574
        for(ull i=0;i<=border;i++) d[i]=other[i];
    }
    //field& operator=(field<H> &&other) noexcept {
    template<typename N>ull coordZuID(coord<N> x) const {
        ull id=0;
        x*=(N)multiplier;
        auto cvrtCrd=x.round()-(*baseCrd);
        for(di i=0; i<x.dim; i++) {
            ull inRes=(ull)llround((double)cvrtCrd[i]);
            di j=i;
            while(j!=0) {
                j--;
                inRes*=sL[j];
            }
            id+=inRes;
        }
        return id;
    }
    coord<ll> IDzuCoord(di id) const {
        di i=(*baseCrd).dim;
        coord<ll> x(i);
        do {
            i--;
            ll b=pow(sL[i], i);
            x[i]=id/b;
            id-=x[i]*b;
        } while(i!=0);
        x+=(*baseCrd);
        x/=multiplier;
        return x;
    }
//    ull coordZuID(coord<H> x, ull sideLength) { return coordZuID(x.round(), vector<ull>(x.dim, sideLength)); }
//    coord<int> IDzuCoord(int id, di dim, ull sideLength) { return IDzuCoord(id, dim, vector<ull>(dim, sideLength));}
    template<typename D>H& operator[](coord<D> x) {
        auto id=this->coordZuID(x.round());
        return this->d[id];
    }
    template<typename D>H operator[](coord<D> x) const {
        auto id=this->coordZuID(x.round());
        return this->d[id];
    }
    template<typename D>H& operator[](D flatIndex) {
        return this->d[flatIndex];
        //return this->d[flatIndex>border?border:flatIndex];
    }
    H& operator[](ull flatIndex) {
        return this->d[flatIndex];
        //return this->d[flatIndex>border?border:flatIndex];
    }
};

}
#endif
