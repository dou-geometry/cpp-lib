#ifndef __STRUCT_FIELD_HPP__
#define __STRUCT_FIELD_HPP__
#include<line.hh>
namespace d{


    template<typename H> struct field {
        H* d; // [-SL,SL]*[-SL,SL]
        ull border; //max ID
        ull *sL;
        unsigned short multiplier=1;
        d::coord<long long int> *baseCrd;
        field(d::coord<long long int> bl, d::coord<long long int> tr, H val=1) {
            baseCrd=new d::coord<long long int>(bl.round());
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
        field(const d::coord<long long int> sz,H val=1):field(sz*-1, sz, val){}
        template<typename V>field(const d::coord<V> sz, H val=1):field(sz.round(), val){}
        template<typename V>field(const d::coord<V> bl, const d::coord<V> tr, H val=1):field(bl.round(), tr.round(), val){}
        ~field() {
            delete[]d;
            delete[]sL;
            (*baseCrd).~coord();
        }
        field(const field<H> &other): border(other.border) {
            baseCrd=new d::coord<long long int>(*(other.baseCrd));
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
            baseCrd=new d::coord<long long int>(*(other.baseCrd));
            sL=new ull[(*baseCrd).dim];
            for(di i=0;i<(*baseCrd).dim;i++) {
                sL[i]=other.sL[i];
            }
            d=new H[border+1];
            // https://stackoverflow.com/a/29977424/8460574
            for(ull i=0;i<=border;i++) d[i]=other[i];
        }
        //field& operator=(field<H> &&other) noexcept {}
        template<typename N>ull coordZuID(d::coord<N> x) const {
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
        d::coord<ll> IDzuCoord(di id) const {
            di i=(*baseCrd).dim;
            d::coord<ll> x(i);
            do {
                i--;
                di j=i;
                ll b=1;
                while(j!=0) {
                    j--;
                    b*=sL[j];
                }
                x[i]=floor(id/b);
                id-=x[i]*b;
            } while(i!=0);
            x+=(*baseCrd);
            x/=multiplier;
            return x;
        }
        //    ull d::coordZuID(d::coord<H> x, ull sideLength) { return d::coordZuID(x.round(), vector<ull>(x.dim, sideLength)); }
        //    d::coord<int> IDzuCoord(int id, di dim, ull sideLength) { return IDzuCoord(id, dim, vector<ull>(dim, sideLength));}
        template<typename D>H& operator[](d::coord<D> x) {
            auto id=this->coordZuID(x.round());
            return this->d[id];
        }
        template<typename D>H operator[](d::coord<D> x) const {
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
