#ifndef __CAR_LINEAR_ORICOORD_HPP__
#define __CAR_LINEAR_ORICOORD_HPP__
#define di long unsigned int
#define ull unsigned long long int
#define ll long long int
#include<coord.hh>
#include<nonDim.hh>
#include<units.hh>
#include<concepts>
#include <initializer_list>
#include <iostream>
#include<cmath>
#include <utility>
#include <cstring>
#include<complex>

namespace d {
    struct polarcoord:d::compact::coord<double, 2> { // Only using double
        polarcoord(double r, double theta): d::compact::coord<double, 2>({r, theta}) {}
        using d::compact::coord<double, 2>::coord;
        inline double norm() const;
        inline double norm2() const;
        polarcoord& pow(double p);
        polarcoord pow(double p) const;
        polarcoord unit() const;
        polarcoord abs() const;
        /*
           double dot(const polarcoord &r) const {
           auto res=*this;
           for(di i=0; i<r.dim; i++) { res.d[i]*=r[i]; };
           double ans=0;
           for(di i=0; i<r.dim; i++) ans+=res.d[i];
           return ans;
           }
           */
        polarcoord& operator+=(const polarcoord&);
        polarcoord& operator-=(const polarcoord&);
        polarcoord& operator*=(const double &r) { this->d[0]*=r; return *this; }
        polarcoord& operator/=(const double &r) { this->d[0]/=r; return *this; }
        // cross product overload
        /*polarcoord& operator*=(const polarcoord &rhs) {
          if(dim!=3 && dim!=7 && dim!=2) throw "Dimension doesn't have cross product operation";
        // 2-D cross product is acheived by little trick that's implemented at operator[], which gives 0 when you read out of range
        if(dim==7) throw "7-D cross product isn't implemented yet";
        if(dim==3) (*this)=polarcoord({
        (*this)[1]*(rhs[2])-(*this)[2]*(rhs[1]),
        (*this)[2]*(rhs[0])-(*this)[0]*(rhs[2]),
        (*this)[0]*(rhs[1])-(*this)[1]*(rhs[0])
        });
        if(dim==2) (*this)=polarcoord({(*this)[0]*(rhs[1])-(*this)[1]*(rhs[0]), 0});
        return *this;
        }*/
        friend std::ostream& operator<<(std::ostream&, const d::polarcoord&);
        void print(int precision=15);
        friend polarcoord operator+(polarcoord lhs, const polarcoord &r) { return lhs+=r; }
        friend polarcoord operator-(polarcoord lhs, const polarcoord &r) { return lhs-=r; }
        friend polarcoord operator*(polarcoord lhs, const double &r) { return lhs*=r; }
        friend polarcoord operator*(const double &r, polarcoord lhs) { return lhs*=r; }
        friend polarcoord operator/(polarcoord lhs, const double &r) { return lhs/=r; }
        friend polarcoord operator/(const double &r, polarcoord lhs) { return lhs/=r; }
        // cross product overload
        //friend polarcoord operator*(polarcoord lhs, const polarcoord &rhs) {return lhs*=rhs;}
        void input();
        static void input(polarcoord&);
        template<typename Z>
            requires (d::nonDim<Z>)
            operator Z() const {
                return (Z)(d[0]);
            }
        template<typename Z>operator d::coord<Z>() const {
            d::coord<Z> res(2);
            res[0]=d[0]*std::cos(d[1]);
            res[1]=d[0]*std::sin(d[1]);
            return res;
        }
        //operator d::compact::coord<double, 2>() = delete;
        d::compact::coord<double, 2> cartesian() const;
        inline double atan2() const;
        //inline double& atan2();
        friend inline double atan2(const polarcoord& x) {
            return x[1];
        }
        //inline static double& atan2(polarcoord&);
    };
    template<typename T>
        coord<T>::coord(const d::polarcoord& x): dim(2) {
            d=new T[dim];
            d[0]=x[0]*std::cos(x[1]);
            d[1]=x[0]*std::sin(x[1]);
        }
    template<typename T>
        coord<T>::coord(d::polarcoord&& x): dim(2) {
            d=new T[dim];
            d[0]=x[0]*std::cos(x[1]);
            d[1]=x[0]*std::sin(x[1]);
        }
}

namespace d::compact {
    //typedef d::polarcoord polarcoord;
    template<typename T, di dimension>
        coord<T, dimension>::coord(const d::polarcoord& x) requires (dimension==2) {
            d[0]=x[0]*std::cos(x[1]);
            d[1]=x[0]*std::sin(x[1]);
        }
    template<typename T, di dimension>
        coord<T, dimension>::coord(d::polarcoord&& x) requires (dimension==2) {
            d[0]=x[0]*std::cos(x[1]);
            d[1]=x[0]*std::sin(x[1]);
        }
}
#endif
