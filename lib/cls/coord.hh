#ifndef __CAR_LINEAR_COORD_HPP__
#define __CAR_LINEAR_COORD_HPP__
#define di long unsigned int
#define ull unsigned long long int
#define ll long long int
#define deg unsigned short
#include"../concepts/nonDim.hh"
#include<concepts>
#include <initializer_list>
#include <iostream>
#include<cmath>
#include <utility>
#include <cstring>
#include<complex>
using namespace std;
namespace d {
    template<typename T> struct coord {
        T *d=nullptr;
        long unsigned int dim;
        //coord(int dim, T val=0.0): d(dim, val), dim(dim) {}
        coord(di dim, T val=0): dim(dim) {
            d=new T[dim];
            for(di i=0;i<dim;i++) {
                d[i]=val;
            }
        }
        coord(double r, deg theta, deg phi, double divisor=1.0) { // theta<-[0,360), phi<-[0,180]
            dim=3;
            double t=(double)theta/divisor/180*M_PI, p=(double)phi/divisor/180*M_PI;
            d={r*cos(t)*sin(p),r*sin(t)*sin(p),r*cos(p)};
        }
        coord(double r, deg theta, double divisor=1.0) {
            dim=2;
            double t=(double)theta/divisor/180*M_PI;
            d={r*cos(t), r*sin(t)};
        }
        coord(std::initializer_list<T> l): dim{l.size()} {
            //printf("init %p\n", this);
            //d=(T *)calloc(dim, sizeof(T));
            d=new T[dim];
            memcpy(d, l.begin(), sizeof(T)*dim);
            //std::copy(l.begin(), l.end(), d);
        }
        coord(std::complex<T> z): coord({z.real(), z.imag()}) {}
        coord(): coord(2, (T)0){}
        ~coord() {
            delete[]d;
        }
        coord(const coord<T> &other): dim(other.dim) {
            //printf("copy ro3");
            d=new T[dim];
            //printf("%p=>%p\n", &other.d, &d);
            memcpy(d, other.d, sizeof(T)*dim);
        }
        coord(coord<T> &&other) noexcept: d(exchange(other.d, nullptr)), dim(exchange(other.dim,(di)0)) {}
        coord& operator=(const coord<T> &other) {
            //printf("move ro3");
            if (this == &other) return *this;
            dim=other.dim;
            delete[]d;
            d=new T[dim];
            memcpy(d, other.d, sizeof(T)*dim);
            return *this;
        }
        coord& operator=(coord<T> &&other) noexcept {
            swap(dim, other.dim);
            swap(d, other.d);
            return *this;
        }
        double norm() const {
            double res=0;
            for(di i=0; i<dim; i++) {
                res+=std::pow(this->d[i],2.0);
            }
            return sqrt(res);
        }
        double norm2() const {
            double res=0;
            for(di i=0; i<dim; i++) {
                res+=pow(this->d[i],2.0);
            }
            return (res);
        }
        coord& pow(double p) {
            for(di i=0; i<dim; i++)
                d[i]=std::pow(d[i], p);
            return *this;
        }
        coord pow(double p) const {
            auto res(*this);
            for(di i=0; i<res.dim; i++)
                res.d[i]=std::pow(res.d[i], p);
            return res;
        }
        coord<T> unit() const {
            return (*this)/(this->norm());
        }
        coord<long long int> round() const {
            coord<long long int> crd(dim, 0);
            for(di i=0;i<dim;i++) {
                crd[i]+=llround((double)d[i]);
            }
            return crd;
        }
        coord<ll> rupper() const {
            coord<long long int> crd(dim, 0);
            for(di i=0; i<crd.dim; i++) crd[i]=floor((double)d[i]+0.5);
            return crd;
        }
        coord<double> round(int digits) const {
            coord<double> crd(dim, 0);
            double r=pow(10, digits);
            for(di i=0; i<dim; i++) {
                crd[i]+=llrind((d[i]*r))/r;
            }
            return crd;
        }
        coord<T> abs() const {
            coord<T> res(this->dim);
            for(di i=0; i<this->dim; i++) { res[i]=fabs(this->d[i]); }
            return res;
        }
        coord<ull> unsign() const {
            coord<ull> crd(dim, (ull)0);
            for(di i=0;i<dim;i++) {
                crd[i]=(ull)llabs(llround((double)d[i]));
            }
            return crd;
        }
        T dot(coord<T> &r) const {
            auto res=*this;
            for(di i=0; i<r.dim; i++) { res.d[i]*=r[i]; };
            double ans=0;
            for(di i=0; i<r.dim; i++) ans+=d[i];
            return ans;
        }
        coord<T>& operator+=(const coord<T> &r) {
            if(r.dim>this->dim) {
                throw "Addition's rhs has larger Dimension than lhs.";
            }
            for(di i=0; i<r.dim; i++) { this->d[i]+=r[i]; }
            return *this;
        }
        coord<T>& operator-=(const coord<T> &r) { for(di i=0; i<r.dim; i++) { this->d[i]-=r[i]; }; return *this; }
        coord<T>& operator*=(const T &r) { for(di i=0; i<this->dim; i++) { this->d[i]*=r; }; return *this; }
        coord<T>& operator/=(const T &r) { for(di i=0; i<this->dim; i++) { this->d[i]/=r; }; return *this; }
        // cross product overload
        coord<T>& operator*=(const coord<T> &rhs) {
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
        T& operator[](int i) {
            return d[i];
        }
        T operator[](int i) const {
            return d[i];
        }
        friend std::ostream& operator<<(std::ostream& os, const coord<T> &crd) {
            os << "(" << crd[0];
            for(di i=1;i<crd.dim;i++) {
                os << ", " << crd[i];
            }
            os << ")";
            return os;
        }
        void print(int precision=15) {
            printf("(%.*lf", precision, *d);
            for(di i=1; i<dim; i++) {
                printf(", %.*lf", precision, *(d+i));
            }
            printf(")\n");
        }
        friend coord<T> operator+(coord<T> lhs, const coord<T> &r) { return lhs+=r; }
        friend coord<T> operator-(coord<T> lhs, const coord<T> &r) { return lhs-=r; }
        template<typename O> friend coord<T> operator*(coord<T> lhs, const O &r) { return lhs*=(T)r; }
        template<typename O> friend coord<T> operator*(const O &r, coord<T> lhs) { return lhs*=(T)r; }
        template<typename O> friend coord<T> operator/(coord<T> lhs, const O &r) { return lhs/=(T)r; }
        template<typename O> friend coord<T> operator/(const O &r, coord<T> lhs) { return lhs/=(T)r; }
        // cross product overload
        friend coord<T> operator*(coord<T> lhs, const coord<T> &rhs) {return lhs*=rhs;}
        void input() {
            for(di i=0; i<dim; i++) {
                cin >> d[i];
            }
        }
        static void input(coord<T> &x) {
            cout << "Please enter coordinate with each parameter seperated by space: ";
            x.input();
        }
        template<typename Z>
            requires (d::nonDim<Z>)
            operator Z() const {
                Z res=1;
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
}
#endif
