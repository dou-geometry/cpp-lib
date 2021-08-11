#pragma once
#define di long unsigned int
#define ull unsigned long long int
#define ll long long int
#define deg unsigned short
#include"../../concepts/nonDim.hh"
#include<concepts>
#include <initializer_list>
#include <iostream>
#include<cmath>
#include <utility>
#include <cstring>
#include<complex>
namespace d::compact {
    template<typename T, di dimension=1>
        struct coord {
            T d[dimension];
            //static constexpr di dim=dimension;
            coord(T val=0) {
                for(di i=0; i<dimension; ++i)
                    d[i]=val;
            }
            coord(std::initializer_list<T> l) {
                //assert(l.size()<=dimension);
                memcpy(d, l.begin(), sizeof(T)*dimension);
            }
            ~coord() {//Not VLA so no need to destruct?
            }
            coord(const coord<T, dimension> &other) {
                memcpy(d, other.d, sizeof(T)*dimension);
            }
            coord(coord<T, dimension> &&other) noexcept {
                std::swap(d, other.d);
            }
            coord& operator=(const coord<T, dimension> &other) {
                //printf("move ro3");
                if (this == &other) return *this;
                memcpy(d, other.d, sizeof(T)*dimension);
                return *this;
            }
            coord& operator=(coord<T, dimension> &&other) noexcept {
                swap(d, other.d);
                return *this;
            }
            double norm() const {
                double res=0;
                for(di i=0; i<dimension; i++) {
                    res+=std::pow(this->d[i],2.0);
                }
                return sqrt(res);
            }
            double norm2() const {
                double res=0;
                for(di i=0; i<dimension; i++) {
                    res+=std::pow(this->d[i],2.0);
                }
                return (res);
            }
            coord& pow(double p) {
                for(di i=0; i<dimension; i++)
                    d[i]=std::pow(d[i], p);
                return *this;
            }
            coord pow(double p) const {
                auto res(*this);
                for(di i=0; i<dimension; i++)
                    res.d[i]=std::pow(res.d[i], p);
                return res;
            }
            coord<T, dimension> unit() const {
                return (*this)/(this->norm());
            }
            coord<long long int, dimension> round() const {
                coord<long long int, dimension> crd(0);
                for(di i=0;i<dimension;i++) {
                    crd[i]+=llround((double)d[i]);
                }
                return crd;
            }
            coord<ll, dimension> rupper() const {
                coord<long long int, dimension> crd(0);
                for(di i=0; i<dimension; i++) crd[i]=floor((double)d[i]+0.5);
                return crd;
            }
            coord<double, dimension> round(int digits) const {
                coord<double, dimension> crd(0);
                double r=pow(10, digits);
                for(di i=0; i<dimension; i++) {
                    crd[i]+=llrind((d[i]*r))/r;
                }
                return crd;
            }
            coord<T, dimension> abs() const {
                coord<T, dimension> res;
                for(di i=0; i<dimension; i++) { res[i]=fabs(this->d[i]); }
                return res;
            }
            coord<ull, dimension> unsign() const {
                coord<ull, dimension> crd((ull)0);
                for(di i=0;i<dimension;i++) {
                    crd[i]=(ull)llabs(llround((double)d[i]));
                }
                return crd;
            }
            T dot(const coord<T, dimension> &r) const {
                auto res=*this;
                for(di i=0; i<dimension; i++) { res.d[i]*=r[i]; };
                double ans=0;
                for(di i=0; i<dimension; i++) ans+=res.d[i];
                return ans;
            }
            coord<T, dimension>& operator+=(const coord<T, dimension> &r) {
                for(di i=0; i<dimension; i++) { this->d[i]+=r[i]; }
                return *this;
            }
            coord<T, dimension>& operator-=(const coord<T, dimension> &r) { for(di i=0; i<dimension; i++) { this->d[i]-=r[i]; }; return *this; }
            coord<T, dimension>& operator*=(const T &r) { for(di i=0; i<dimension; i++) { this->d[i]*=r; }; return *this; }
            coord<T, dimension>& operator/=(const T &r) { for(di i=0; i<dimension; i++) { this->d[i]/=r; }; return *this; }
            // cross product overload
            coord<T, dimension>& operator*=(const coord<T, dimension> &rhs) {
                static_assert(dimension!=3 && dimension!=7 && dimension!=2, "Dimension doesn't have cross product operation");
                // 2-D cross product is acheived by little trick that's implemented at operator[], which gives 0 when you read out of range
                if constexpr(dimension==7) throw "7-D cross product isn't implemented yet";
                if constexpr(dimension==3) (*this)=coord<T>({
                        (*this)[1]*(rhs[2])-(*this)[2]*(rhs[1]),
                        (*this)[2]*(rhs[0])-(*this)[0]*(rhs[2]),
                        (*this)[0]*(rhs[1])-(*this)[1]*(rhs[0])
                        });
                if constexpr(dimension==2) (*this)=coord<T>({(*this)[0]*(rhs[1])-(*this)[1]*(rhs[0]), 0});
                return *this;
            }
            T& operator[](int i) {
                return d[i];
            }
            T operator[](int i) const {
                return d[i];
            }
            friend std::ostream& operator<<(std::ostream& os, const coord<T, dimension> &crd) {
                os << "(" << crd[0];
                for(di i=1;i<dimension;i++) {
                    os << ", " << crd[i];
                }
                os << ")";
                return os;
            }
            void print(int precision=15) {
                printf("(%.*lf", precision, *d);
                for(di i=1; i<dimension; i++) {
                    printf(", %.*lf", precision, *(d+i));
                }
                printf(")\n");
            }
            friend coord<T, dimension> operator+(coord<T, dimension> lhs, const coord<T, dimension> &r) { return lhs+=r; }
            friend coord<T, dimension> operator-(coord<T, dimension> lhs, const coord<T, dimension> &r) { return lhs-=r; }
            template<typename O> requires std::convertible_to<O, T> friend coord<T, dimension> operator*(coord<T, dimension> lhs, const O &r) { return lhs*=(T)r; }
            template<typename O> requires std::convertible_to<O, T> friend coord<T, dimension> operator*(const O &r, coord<T, dimension> lhs) { return lhs*=(T)r; }
            template<typename O> requires std::convertible_to<O, T> friend coord<T, dimension> operator/(coord<T, dimension> lhs, const O &r) { return lhs/=(T)r; }
            template<typename O> requires std::convertible_to<O, T> friend coord<T, dimension> operator/(const O &r, coord<T, dimension> lhs) { return lhs/=(T)r; }
            // cross product overload
            friend coord<T, dimension> operator*(coord<T, dimension> lhs, const coord<T, dimension> &rhs) {return lhs*=rhs;}
            void input() {
                for(di i=0; i<dimension; i++) {
                    std::cin >> d[i];
                }
            }
            static void input(coord<T, dimension> &x) {
                std::cout << "Please enter coordinate with each parameter seperated by space: ";
                x.input();
            }
            template<typename Z>
                requires (d::nonDim<Z>)
                operator Z() const {
                    Z res=1;
                    for(di i=0; i<dimension; i++) res*=this->d[i];
                    return res;
                }
            template<typename Z>operator coord<Z, dimension>() const {
                coord<Z, dimension> res;
                for(di i=0; i<dimension; i++) res[i]=(Z)d[i];
                return res;
            }
            auto inv() const {
                auto res=*this;
                for(di i=0; i<dimension; i++) res[i]=((T)1)/res[i];
                return res;
            }
            T sum() const {
                T res;
                for(di i=0; i<dimension; i++) res+=this->d[i];
                return res;
            }
        };
}
