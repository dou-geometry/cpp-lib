// https://qiita.com/agate-pris/items/1b29726935f0b6e75768
// https://qiita.com/MoriokaReimen/items/7c83ebd0fbae44d8532d
#ifndef   CLS_HPP
#define   CLS_HPP

#include<bits/stdc++.h>
using namespace std;
#define dt 1e-20
#define RES 3
#define SL 1000000 //sideLength
#define angIncr 1e-12
#define DxIncr 1e-4 //must be way smaller than resolution

#ifdef __NVCC__
#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort=true)
{
   if (code != cudaSuccess) 
   {
      fprintf(stderr,"GPUassert: %s %s %d\n", cudaGetErrorString(code), file, line);
      if (abort) exit(code);
   }
}
//https://stackoverflow.com/a/14038590/8460574
#endif

#ifdef __CUDA_ARCH__
#define CF __device__
#else
#define CF
#endif

template<typename G>
struct mono {
    coord<G> pos,vel;
    mono(di dim=3) {
        coord<G> pos(dim);
        coord<G> vel(dim);
    }
};



struct cov:field<bool> {
    di resolution=1;
    CF cov(coord<long long int> bl, coord<long long int> tr, di r=1): field<bool>(bl, tr, false), resolution(r) {}
    CF cov(const coord<long long int> sz, di r=1):cov(sz*-1LL, sz, r){}
    template<typename T>CF cov(const coord<T> sz, di r=1):cov(sz.round(), r){}
    template<typename T>CF cov(const coord<T> bl, const coord<T> tr, di r=1):cov(bl.round(), tr.round(), r) {}
    template<typename C>CF ull calc(line<C> l) {
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
    template<typename D>CF ull set(coord<D> y, ll res=1) {
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
    CF cov& reset() {
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


namespace settings {
    struct out {
        static void stable() { std::cout.precision(15); return; }
        static void unstable() { std::cout.precision(17); return; }
        static void showZero() {
            std::cout.unsetf(std::ios::floatfield);
            std::cout.setf( std::ios::fixed, std:: ios::floatfield );
            return;
        }
    };
};

#endif // CLS_HPP
