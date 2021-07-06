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
#define di long unsigned int
#define ull unsigned long long int
#define ll long long int
#define deg unsigned short

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

template<typename T>
struct coord {
    T *d;
    long unsigned int dim;
    //coord(int dim, T val=0.0): d(dim, val), dim(dim) {}
    CF coord(di dim, T val=0.0): dim(dim) {
        d=new T[dim];
        for(di i=0;i<dim;i++) {
            d[i]=val;
        }
    }
    CF coord(double r, deg theta, deg phi, double divisor=1.0) { // theta<-[0,360), phi<-[0,180]
        dim=3;
        double t=(double)theta/divisor/180*M_PI, p=(double)phi/divisor/180*M_PI;
        d={r*cos(t)*sin(p),r*sin(t)*sin(p),r*cos(p)};
    }
    CF coord(double r, deg theta, double divisor=1.0) {
        dim=2;
        double t=(double)theta/divisor/180*M_PI;
        d={r*cos(t), r*sin(t)};
    }
    CF coord(initializer_list<T> l): dim{l.size()} {
        //printf("init %p\n", this);
        //d=(T *)calloc(dim, sizeof(T));
        d=new T[dim];
        memcpy(d, l.begin(), sizeof(T)*dim);
        //std::copy(l.begin(), l.end(), d);
    }
    CF coord(): coord(2, (T)0){}
    CF ~coord() {
        #ifdef __NVCC__
            #ifdef __CUDA_ARCH__
            //delete[]d;
            free(d);
            #else
            cudaPointerAttributes attributes;
            gpuErrchk(cudaPointerGetAttributes(&attributes, d));
            if(attributes.type == 0) {
                free(d);
            } else if(attributes.type==1) {
                free(d);
            } else if(attributes.type==2) {
                gpuErrchk(cudaFree(d));
            } else {
                // This is cudaMemoryTypeManaged memory, which no idea what this is...
            }
            #endif
        #else
            delete[]d;
        #endif
    }
    CF coord(const coord<T> &other): dim(other.dim) {
        //printf("copy ro3");
        d=new T[dim];
        //printf("%p=>%p\n", &other.d, &d);
        memcpy(d, other.d, sizeof(T)*dim);
    }
    CF coord(coord<T> &&other) noexcept: d(std::exchange(other.d, nullptr)), dim(std::exchange(other.dim,(di)0)) {}
    CF coord& operator=(const coord<T> &other) {
        //printf("move ro3");
        if (this == &other) return *this;
        dim=other.dim;
        d=new T[dim];
        memcpy(d, other.d, sizeof(T)*dim);
        return *this;
    }
    CF coord& operator=(coord<T> &&other) noexcept {
#ifdef __CUDA_ARCH__
        auto tmp=dim;
        dim=other.dim;
        other.dim=tmp;
        auto tt=d;
        d=other.d;
        other.d=tt;
#else
        swap(dim, other.dim);
        swap(d, other.d);
#endif
        return *this;
    }
#ifdef __NVCC__
    coord<T>* push() {
        auto cpy=*this;
        coord<T> *dest;
        auto nB=sizeof(cpy);
        auto dB=sizeof(T)*dim;
        auto oldAdr=cpy.d;
        gpuErrchk(cudaMalloc((void **) &dest, nB));
        gpuErrchk(cudaMalloc((void **) &(cpy.d), dB));
        gpuErrchk(cudaMemcpy(cpy.d, (*this).d, dB, cudaMemcpyHostToDevice));
        gpuErrchk(cudaMemcpy(dest, &cpy, nB, cudaMemcpyHostToDevice));
        cpy.d=oldAdr;
        //cout << "Rmed: " << cpy.d << endl;
        return dest;
    }
    coord<T>* pull() {
        auto nB=sizeof(*this);
        coord<T> *dest=(coord<T> *)malloc(nB);
        gpuErrchk(cudaMemcpy(dest, this, nB, cudaMemcpyDeviceToHost));
        auto pBk=(*dest).d; //pointer backup
        (*dest).d=new T[(*dest).dim];
        auto dB=sizeof(T)*((*dest).dim);
        cudaMemcpy((*dest).d, pBk, dB, cudaMemcpyDeviceToHost);
        return dest;
    }
#endif
    CF double norm() const {
        double res=0;
        for(di i=0; i<dim; i++) {
            res+=pow(this->d[i],2.0);
        }
        return sqrt(res);
    }
    CF double norm2() const {
        double res=0;
        for(di i=0; i<dim; i++) {
            res+=pow(this->d[i],2.0);
        }
        return (res);
    }
    CF coord<T> unit() {
        return (*this)/(this->norm());
    }
    CF coord<long long int> round() const {
        coord<long long int> crd(dim, 0);
        for(di i=0;i<dim;i++) {
            crd[i]+=llround((double)d[i]);
        }
        return crd;
    }
    CF coord<ll> rupper() const {
        coord<long long int> crd(dim, 0);
        for(di i=0; i<crd.dim; i++) crd[i]=floor((double)d[i]+0.5);
        return crd;
    }
    CF coord<double> round(int digits) const {
        coord<double> crd(dim, 0);
        double r=pow(10, digits);
        for(di i=0; i<dim; i++) {
            crd[i]+=llrind((d[i]*r))/r;
        }
        return crd;
    }
    CF coord<T> abs() {
        coord<T> res(this->dim);
        for(di i=0; i<this->dim; i++) { res[i]=fabs(this->d[i]); }
        return res;
    }
    CF coord<ull> unsign() const {
        coord<ull> crd(dim, (ull)0);
        for(di i=0;i<dim;i++) {
            crd[i]=(ull)llabs(llround((double)d[i]));
        }
        return crd;
    }
    CF T dot(coord<T> &r) const {
        auto res=*this;
        for(di i=0; i<r.dim; i++) { res.d[i]*=r[i]; };
        double ans=0;
        for(auto &i:res.d) ans+=i;
        return ans;
    }
//    void loopTo(coord<T> dest, void(*f)(coord<T> x)) const {
//        dest-=*this;
//        //field tmp(coord(dest.dim), dest);
//        int end=field::coordZuID(dest, dest.d);
//        for(int i=0; i<=end; i++) {
//            (*f)(field::IDzuCoord(i, dest.dim, dest.d)+*this);
//        }
//        return;
//    }
    CF coord<T>& operator+=(const coord<T> &r) {
        //for(int i=0; i<(r.dim<this->dim?r.dim:this->dim); i++) {
//        if(r.dim>this->dim) {
//            throw "Addition's rhs has larger Dimension than lhs.";
//        }
        for(di i=0; i<r.dim; i++) { this->d[i]+=r[i]; }
        return *this;
    }
    CF coord<T>& operator-=(const coord<T> &r) { for(di i=0; i<r.dim; i++) { this->d[i]-=r[i]; }; return *this; }
    CF coord<T>& operator*=(const T &r) { for(di i=0; i<this->dim; i++) { this->d[i]*=r; }; return *this; }
    CF coord<T>& operator/=(const T &r) { for(di i=0; i<this->dim; i++) { this->d[i]/=r; }; return *this; }
        // cross product overload
    CF coord<T>& operator*=(const coord<T> &rhs) {
        if(dim!=3 && dim!=7 && dim!=2) throw "Dimension doesn't have cross product operation";
        // 2-D cross product is acheived by little trick that's implemented at operator[], which gives 0 when you read out of range
        if(dim==7) throw "7-D cross product isn't implemented yet";
        if(dim==3) (*this)=coord<T>({
                (*this)[1]*(rhs[2])-(*this)[2]*(rhs[1]),
                (*this)[2]*(rhs[0])-(*this)[0]*(rhs[2]),
                (*this)[0]*(rhs[1])-(*this)[1]*(rhs[0])
        });
        if(dim==2) (*this)=coord<T>({(*this)[0]*(rhs[1])-(*this)[1]*(rhs[0]), 0});
        return *this;
    }
    CF T& operator[](int i) {
        //return i<dim?d[i]:(T)0;
        return d[i];
    }
    CF T operator[](int i) const {
        return d[i];
        //return i<dim?d[i]:(T)0;
    }
    friend ostream& operator<<(ostream& os, const coord<T> &crd) {
        os << "(" << crd[0];
        for(di i=1;i<crd.dim;i++) {
            os << ", " << crd[i];
        }
        os << ")";
        return os;
    }
    CF void print(int precision=15) {
#ifdef __CUDA_ARCH__
        printf("(%.15lf", *d);
#else
        printf("(%.*lf", precision, *d);
#endif
        for(di i=1; i<dim; i++) {
#ifdef __CUDA_ARCH__
            printf(", %.15lf", *(d+i));
#else
            printf(", %.*lf", precision, *(d+i));
#endif
        }
        printf(")\n");
    }
    CF friend coord<T> operator+(coord<T> lhs, const coord<T> &r) { return lhs+=r; }
    CF friend coord<T> operator-(coord<T> lhs, const coord<T> &r) { return lhs-=r; }
    CF friend coord<T> operator*(coord<T> lhs, const T &r) { return lhs*=r; }
    CF friend coord<T> operator/(coord<T> lhs, const T &r) { return lhs/=r; }
    // cross product overload
    CF friend coord<T> operator*(coord<T> lhs, const coord<T> &rhs) {return lhs*=rhs;}
    void input() {
        for(di i=0; i<dim; i++) {
            cin >> d[i];
        }
    }
    static void input(coord<T> &ptr) {
        cout << "Please enter coordinate with each parameter seperated by space: ";
        (ptr).input();
    }
    operator T() const {
        T res=1;
        for(di i=0; i<dim; i++) res*=this->d[i];
        return res;
    }
    template<typename Z>operator coord<Z>() const {
        coord<Z> res(this->dim);
        for(di i=0; i<dim; i++) res[i]=(Z)d[i];
        return res;
    }
    auto inv() const {
        auto res=*this;
        for(di i=0; i<dim; i++) res[i]=((T)1)/res[i];
        return res;
    }
    T sum() const {
        T res;
        for(di i=0; i<dim; i++) res+=this->d[i];
        return res;
    }
};

template<typename G>
struct mono {
    coord<G> pos,vel;
    mono(di dim=3) {
        coord<G> pos(dim);
        coord<G> vel(dim);
    }
};

template<typename H>
struct field {
    H* d; // [-SL,SL]*[-SL,SL]
    ull border; //max ID
    ull *sL;
    unsigned short multiplier=1;
    coord<long long int> *baseCrd;
    CF field(coord<long long int> bl, coord<long long int> tr, H val=1) {
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
    CF field(const coord<long long int> sz,H val=1):field(sz*-1, sz, val){}
    template<typename T>CF field(const coord<T> sz, H val=1):field(sz.round(), val){}
    template<typename T>CF field(const coord<T> bl, const coord<T> tr, H val=1):field(bl.round(), tr.round(), val){}
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
    CF ~field() {
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
    CF field(const field<H> &other): border(other.border) {
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
    CF field& operator=(const field<H> &other) {
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
    template<typename T>CF ull coordZuID(coord<T> x) const {
        ull id=0;
        x*=(T)multiplier;
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
    CF coord<ll> IDzuCoord(di id) const {
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
    template<typename T>CF H& operator[](coord<T> x) {
        auto id=this->coordZuID(x.round());
        return this->d[id];
    }
    template<typename T>CF H operator[](coord<T> x) const {
        auto id=this->coordZuID(x.round());
        return this->d[id];
    }
    template<typename D>CF H& operator[](D flatIndex) {
        return this->d[flatIndex];
        //return this->d[flatIndex>border?border:flatIndex];
    }
    CF H& operator[](ull flatIndex) {
        return this->d[flatIndex];
        //return this->d[flatIndex>border?border:flatIndex];
    }
};

template<typename T>
struct line {
    coord<T> s, t, d;
    line(coord<T> a, coord<T> b): s(a), t(b), d((b-a).unit()){}
    ~line() {
        s.~coord();
        t.~coord();
    }
    double dist(const coord<T> Punkt) {
        double t=(Punkt-s).dot(d);
        auto oLP=s+d*t;
        return (Punkt-oLP).norm();
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

#define nx n[0]
#define ny n[1]
#define nz n[2]
CF coord<double> R(coord<double> n, double theta, coord<double> target) { //3D only
    double st=sin(theta/180*M_PI), ct=cos(theta/180*M_PI);
    double nx2=pow(nx,2.0), ny2=pow(ny,2.0), nz2=pow(nz,2.0);
    coord<double> res={
        (double)(ct+nx2*(1-ct))*target[0]+(nx*ny*(1-ct)-nz*st)*target[1]+(nz*nx*(1-ct)+ny*st)*target[2],
        (double)(nx*ny*(1-ct)+nz*st)*target[0]+(ct+ny2*(1-ct))*target[1]+(ny*nz*(1-ct)-nx*st)*target[2],
        (double)(nz*nx*(1-ct)-ny*st)*target[0]+(ny*nz*(1-ct)+nx*st)*target[1]+(ct+nz2*(1-ct))*target[2]
    };
    return res;
}

template<typename T>
struct matrix {
    T** d;
    di x, y;
    CF matrix(di dimX, di dimY): x(dimX), y(dimY) {
        //d=(T **)calloc(dimX, sizeof(T*));
        d=new T*[dimX];
        for(di i=0; i<dimX; i++) d[i]=new T[dimY];
    }
    CF ~matrix() {
        #ifdef __NVCC__
            #ifdef __CUDA_ARCH__
            //delete[]d;
            for(di i=0; i<x; i++) free(d[i]);
            free(d);
            #else
            cudaPointerAttributes attributes;
            gpuErrchk(cudaPointerGetAttributes(&attributes, d));
            if(attributes.type == 0) {
                for(di i=0; i<x; i++) free(d[i]);
                free(d);
            } else if(attributes.type==1) {
                for(di i=0; i<x; i++) free(d[i]);
                free(d);
            } else if(attributes.type==2) {
                for(di i=0; i<x; i++) cudaFree(d[i]);
                cudaFree(d);
            } else {
                // This is cudaMemoryTypeManaged memory, which no idea what this is...
            }
            #endif
        #else
            for(di i=0; i<x; i++) delete[](d[i]);
            delete[]d;
        #endif
    }
    CF matrix(const matrix<T> &other): x(other.x), y(other.y) {
        //printf("copy ro3");
        d=new T*[x];
        for(di i=0; i<x; i++) d[i]=new T[y];
        for(di i=0; i<x; i++) memcpy(d[i], other.d[i], sizeof(T)*y);
    }
    //CF coord(coord<T> &&other) noexcept: d(std::exchange(other.d, nullptr)), dim(std::exchange(other.dim,(di)0)) {}
    CF matrix& operator=(const matrix<T> &other) {
        //printf("move ro3");
        if (this == &other) return *this;
        x=other.x;
        y=other.y;
        d=new T*[x];
        for(di i=0; i<x; i++) d[i]=new T[y];
        for(di i=0; i<x; i++) memcpy(d[i], other.d[i], sizeof(T)*y);
    }
    CF matrix& operator=(matrix<T> &&other) noexcept {
#ifdef __CUDA_ARCH__
        auto tmp=x;
        x=other.x;
        other.x=tmp;
        tmp=y;
        y=other.y;
        other.y=tmp;
        auto tt=d;
        d=other.d;
        other.d=tt;
#else
        swap(x, other.x);
        swap(y, other.y);
        swap(d, other.d);
#endif
        return *this;
    }
#ifdef __NVCC__
    matrix<T>* push() {
        auto cpy=*this;
        auto nB=sizeof(T*)*x;
        auto oldd=new T*[x];
        memcpy(oldd, cpy.d, nB);
        matrix<T> *dest;
        cudaMalloc((void **) &dest, sizeof(cpy));
        for(di i=0; i<x; i++) gpuErrchk(cudaMalloc((void **) &cpy.d[i], sizeof(T)*y));
        for(di i=0; i<x; i++) gpuErrchk(cudaMemcpy(cpy.d[i], oldd[i], sizeof(T)*y, cudaMemcpyHostToDevice));
        auto oldAdr=cpy.d;
        gpuErrchk(cudaMalloc((void **) &cpy.d, nB));
        gpuErrchk(cudaMemcpy(cpy.d, oldAdr, nB, cudaMemcpyHostToDevice));
        gpuErrchk(cudaMemcpy(dest, &cpy, sizeof(cpy), cudaMemcpyHostToDevice));
        cpy.d=oldAdr;
        memcpy(cpy.d, oldd, nB);
        return dest;
    }
#endif
    template<typename F> CF T* operator[](F i) { return d[i]; };
    template<typename F> CF T* operator[](F i) const { return d[i]; };
    friend ostream& operator<<(ostream& os, matrix<T> &crd) {
        os << "[" << crd[0][0];
        for(di i=1;i<crd.x;i++) {
            os << ", " << crd[i][0];
        }
        os << "]";
        for(di r=1; r<crd.y; r++) {
            os << endl << "[" << crd[0][r];
            for(di i=1;i<crd.x;i++) {
                os << ", " << crd[i][r];
            }
            os << "]";
        }
        return os;
    }
    CF void print(int precision=15) {
#ifdef __CUDA_ARCH__
        printf("[%.15lf", d[0][0]);
#else
        printf("[%.*lf", precision, d[0][0]);
#endif
        for(di i=1;i<x;i++) {
#ifdef __CUDA_ARCH__
            printf(", %.15lf", d[i][0]);
#else
            printf(", %.*lf", precision, d[i][0]);
#endif
        }
        printf("]");
        for(di r=1; r<y; r++) {
#ifdef __CUDA_ARCH__
            printf("\n[%.15lf", d[0][r]);
#else
            printf("\n[%.*lf", precision, d[0][r]);
#endif
            for(di i=1;i<x;i++) {
#ifdef __CUDA_ARCH__
                printf(", %.15lf", d[i][r]);
#else
                printf(", %.*lf", precision, d[i][r]);
#endif
            }
            printf("]");
        }
        return;
    }
    CF friend matrix<T> operator*(matrix<T> lhs, matrix<T> rhs) {
        matrix<double> res(rhs.x, lhs.y);
        for(di r=0; r<rhs.x; r++) {
            for(di c=0; c<lhs.y; c++) {
                for(di i=0; i<lhs.x; i++) {
                    res[r][c]+=lhs[i][c]*rhs[r][i];
                }
            }
        }
        return res;
    }
    CF coord<T> toCoord() {
        coord<T> res(y);
        for(di i=0; i<y; i++) res[i]=d[0][i];
        return res;
    }
    CF friend coord<T> operator*(const matrix<T> lhs, coord<T> rhs) {
        coord<T> res(lhs.y, (T)0);
        for(di i=0; i<res.dim; i++) {
            for(di j=0; j<res.dim; j++) res[i]+=lhs[j][i]*rhs[j];
        }
        return res;
    }
    CF static matrix<T> I(di s) {
        matrix<T> res(s, s);
        for(di i=0; i<s; i++) res[i][i]=1;
        return res;
    }
    CF static matrix<T> R(double theta) {
        matrix<T> res(2, 2);
        res[0][0]=cos(theta);
        res[1][0]=-sin(theta);
        res[0][1]=sin(theta);
        res[1][1]=cos(theta);
        return res;
    }
    CF static matrix<T> Rx(double theta) {
        matrix<T> res(3, 3);
        T   a[3]={1, 0, 0},
            b[3]={0, cos(theta), sin(theta)},
            c[3]={0, -sin(theta), cos(theta)};
        memcpy(res[0], a, sizeof(T)*3);
        memcpy(res[1], b, sizeof(T)*3);
        memcpy(res[2], c, sizeof(T)*3);
        return res;
    }
    CF static matrix<T> Ry(double theta) {
        matrix<T> res(3, 3);
        T   a[3]={cos(theta), 0, -sin(theta)},
            b[3]={0, 1, 0},
            c[3]={sin(theta), 0, cos(theta)};
        memcpy(res[0], a, sizeof(T)*3);
        memcpy(res[1], b, sizeof(T)*3);
        memcpy(res[2], c, sizeof(T)*3);
        return res;
    }
    CF static matrix<T> Rz(double theta) {
        matrix<T> res(3, 3);
        T   a[3]={cos(theta), sin(theta), 0},
            b[3]={-sin(theta), cos(theta), 0},
            c[3]={0, 0, 1};
        memcpy(res[0], a, sizeof(T)*3);
        memcpy(res[1], b, sizeof(T)*3);
        memcpy(res[2], c, sizeof(T)*3);
        return res;
    }
};

template<typename C> //Carrier type
struct Karabinerhaken {
    Karabinerhaken* tugi=nullptr;
    C d;
    CF Karabinerhaken(C x, Karabinerhaken* n=nullptr): d(x), tugi(n){}
    CF ~Karabinerhaken() {
        delete d;
        delete tugi;
    }
    template<typename I>
    CF Karabinerhaken* after(I count) { 
        if(count==0) return this;
        auto midp=(*this).tugi;
        while(--count) {
            midp=midp->tugi;
        }
        return midp;
    }
    CF void insertAfter(Karabinerhaken* mae) {
        tugi=(*mae).tugi;
        (*mae).tugi=this;
        return;
    }
//    CF void insert(aitemu* ptr) {
//        insertAfter(ptr);
//        return;
//    }
//    CF void insertBefore(aitemu* tukiPtr) {
//        //if(tuki!=nullptr) throw "Pointer After!";
//        tuki=tukiPtr;
//        mae=(*tuki).mae;
//        (*tuki).mae=this;
//        if(mae!=nullptr) (*mae).tuki=this;
//        return;
//    }
    CF void insert(Karabinerhaken* ptr1, Karabinerhaken* ptr2) {
        if((*ptr2).tugi==ptr1) return (*this).insertAfter(ptr2);
        return (*this).insertAfter(ptr2);
    }
#ifdef __NVCC__
    Karabinerhaken* push() {
        Karabinerhaken* dest;
        cudaMalloc((void **)&dest, sizeof(*this));
        double *dd=this->d.d;
        cudaMalloc((void **)&dd, sizeof(double)*this->d.dim);
        cudaMemcpy(dd, this->d.d, sizeof(double)*this->d.dim, cudaMemcpyHostToDevice);
        auto oldDD=this->d.d;
        this->d.d=dd;
        cudaMemcpy(dest, this, sizeof(*this), cudaMemcpyHostToDevice);
        this->d.d=oldDD;
        return dest;
    }
#endif
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
