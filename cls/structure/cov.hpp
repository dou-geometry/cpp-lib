#ifndef __CLS_STRUCT_COV__
#define __CLS_STRUCT_COV__

#include"./field.hpp"

struct cov:field<bool> {
    di resolution=1;
    cov(coord<long long int> bl, coord<long long int> tr, di r=1): field<bool>(bl, tr, false), resolution(r) {}
    cov(const coord<long long int> sz, di r=1):cov(sz*-1LL, sz, r){}
    template<typename C>cov(const coord<C> sz, di r=1):cov(sz.round(), r){}
    template<typename C>cov(const coord<C> bl, const coord<C> tr, di r=1):cov(bl.round(), tr.round(), r) {}
    template<typename C>ull calc(line<C> l) {
        if(l.s.dim!=2) throw"This function isn't compatible with dimension!=2";
        ull res=0;
        coord<coord<ll>> genDir(l.s.dim, coord<ll>(l.s.dim, (ll)0));
        /* For Incr=sideLength, 
         * it must either cross 0/1/2 tiles */
        for(di i=0; i<l.s.dim; i++) {
            genDir[i][i]=(l.d[i]>0?1:-1)*resolution;
        }
        // first step
        coord<C> cur=l.s;
        auto curTile=cur.round();
        auto prevTile=curTile;
        bool* ptr=&((*this)[curTile]);
        if(!(*ptr)) res++;
        (*ptr)=true;
        while(true) {
            cur+=l.d;
            curTile=cur.round();
            switch((curTile-prevTile).norm2()) {
                case 1:
                    // neighbouring tile
                    ptr=&((*this)[curTile]);
                    if(!(*ptr)) res++;
                    (*ptr)=true;
                    break;
                case 2:
                    // diagonal tile
                    ptr=&((*this)[curTile]);
                    if(!(*ptr)) res++;
                    (*ptr)=true;
                    auto zuTile=l.dist(prevTile+genDir[0])<=>l.dist(prevTile+genDir[1]);
                    if(zuTile==0) {
                        ptr=&((*this)[prevTile+genDir[0]]);
                        if(!(*ptr)) res++;
                        (*ptr)=true;
                        ptr=&((*this)[prevTile+genDir[1]]);
                        if(!(*ptr)) res++;
                        (*ptr)=true;
                    }
                    if(zuTile<0) ptr=&((*this)[prevTile+genDir[0]]);
                    else if(zuTile>0) ptr=&((*this)[prevTile+genDir[1]]);
                    if(!(*ptr)) res++;
                    (*ptr)=true;
                default:
                    throw"Crossing too many Tiles!";
                    break;
            }
            prevTile=curTile;
            // move to next tile and check if line cross there
        }
        return res;
    }
    template<typename D>ull set(coord<D> y, ll res=1) {
        coord<ll> x=y.rupper();
        switch(res%2) {
            case 1:
                res=(res-1)/2;
                for(ll i=-res; i<=res; i++) for(ll j=-res; j<=res; j++) (*this)[x+coord<ll>({i, j})]=true;
                break;
            case 0:
                res/=2;
                for(ll i=-res; i<res; i++) for(ll j=-res; j<res; j++) (*this)[x+coord<ll>({i, j})]=true;
                break;
            default:
                throw"Unknown case in cov::set()";
                break;
        }
        return (ull)(res*res);
    }
    cov& reset() {
        for(di i=0; i<field<bool>::border; i++) field<bool>::d[i]=false;
        return *this;
    }
    friend ostream& operator<<(ostream& os, const cov &f) {
        cout << (*(f.baseCrd)) << "=>" << f.IDzuCoord(f.border) <<endl;
        for(ll i=(*(f.baseCrd))[0]; i<((*(f.baseCrd))[0]+(ll)(f.sL[0])); i++) {
            for(ll j=(*(f.baseCrd))[1]; j<((*(f.baseCrd))[1]+(ll)(f.sL[1])); j++) {
                os << f[coord<ll>({i, j})];
            }
            os << endl;
        }
        return os;
    }
};

#endif
