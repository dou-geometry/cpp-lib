#ifndef __CAR_LINEAR_ORICOORD_HPP__
#define __CAR_LINEAR_ORICOORD_HPP__
#define di long unsigned int
#define ull unsigned long long int
#define ll long long int
#define deg unsigned short
#include<coord.hh>
#include<nonDim.hh>
#include<concepts>
#include <initializer_list>
#include <iostream>
#include<cmath>
#include <utility>
#include <cstring>
#include<complex>

namespace d {
    struct oricoord:coord<double> { // Only using double
        inline double norm() const;
        inline double norm2() const;
        oricoord& pow(double p);
        oricoord pow(double p) const;
        oricoord unit() const;
        oricoord abs() const;
        /*
        double dot(const oricoord &r) const {
            auto res=*this;
            for(di i=0; i<r.dim; i++) { res.d[i]*=r[i]; };
            double ans=0;
            for(di i=0; i<r.dim; i++) ans+=res.d[i];
            return ans;
        }
        */
        oricoord& operator+=(const oricoord &r) {
            if(r.dim>this->dim) {
                throw "Addition's rhs has larger Dimension than lhs.";
            }
            oricoord res(this->dim);
            auto oriR=d[0];
            d[0]=(oriR*oriR)+(r[0]*r[0])-2.*oriR*r[0]*std::cos(r[1]-d[1]);
            d[1]=d[1]+std::atan2(r[0]*std::sin(r[1]-d[1]), oriR+r[0]*std::cos(r[1]-d[1]));
            //unfinish
            return *this;
            //return res;
        }
        oricoord& operator-=(const oricoord &r) { for(di i=0; i<r.dim; i++) { this->d[i]-=r[i]; }; return *this; }
        oricoord& operator*=(const double &r) { for(di i=0; i<this->dim; i++) { this->d[i]*=r; }; return *this; }
        oricoord& operator/=(const double &r) { for(di i=0; i<this->dim; i++) { this->d[i]/=r; }; return *this; }
        // cross product overload
        oricoord& operator*=(const oricoord &rhs) {
            if(dim!=3 && dim!=7 && dim!=2) throw "Dimension doesn't have cross product operation";
            // 2-D cross product is acheived by little trick that's implemented at operator[], which gives 0 when you read out of range
            if(dim==7) throw "7-D cross product isn't implemented yet";
            if(dim==3) (*this)=oricoord({
                    (*this)[1]*(rhs[2])-(*this)[2]*(rhs[1]),
                    (*this)[2]*(rhs[0])-(*this)[0]*(rhs[2]),
                    (*this)[0]*(rhs[1])-(*this)[1]*(rhs[0])
                    });
            if(dim==2) (*this)=oricoord({(*this)[0]*(rhs[1])-(*this)[1]*(rhs[0]), 0});
            return *this;
        }
        friend std::ostream& operator<<(std::ostream& os, const oricoord &crd) {
            os << "[" << crd[0];
            for(di i=1;i<crd.dim;i++) {
                os << ", " << crd[i];
            }
            os << "]";
            return os;
        }
        void print(int precision=15) {
            printf("[%.*lf", precision, *d);
            for(di i=1; i<dim; i++) {
                printf(", %.*lf", precision, *(d+i));
            }
            printf("]\n");
        }
        friend oricoord operator+(oricoord lhs, const oricoord &r) { return lhs+=r; }
        friend oricoord operator-(oricoord lhs, const oricoord &r) { return lhs-=r; }
        template<typename O> requires std::convertible_to<O, double> friend oricoord operator*(oricoord lhs, const O &r) { return lhs*=(double)r; }
        template<typename O> requires std::convertible_to<O, double> friend oricoord operator*(const O &r, oricoord lhs) { return lhs*=(double)r; }
        template<typename O> requires std::convertible_to<O, double> friend oricoord operator/(oricoord lhs, const O &r) { return lhs/=(double)r; }
        template<typename O> requires std::convertible_to<O, double> friend oricoord operator/(const O &r, oricoord lhs) { return lhs/=(double)r; }
        // cross product overload
        friend oricoord operator*(oricoord lhs, const oricoord &rhs) {return lhs*=rhs;}
        void input() {
            for(di i=0; i<dim; i++) {
                std::cin >> d[i];
            }
        }
        static void input(oricoord &x) {
            std::cout << "Please enter polar coordinate with each parameter seperated by space: ";
            x.input();
        }
        template<typename Z>
            requires (d::nonDim<Z>)
            operator Z() const {
                return (Z)(d[0]);
            }
        template<typename Z>operator coord<Z>() const {
            coord<Z> res(this->dim);
            if(this->dim==2) {
                res[0]=d[0]*std::cos(d[1]);
                res[1]=d[0]*std::sin(d[1]);
            } else { throw "Currently Unsupported"; }
            return res;
        }
    };
}
#endif
