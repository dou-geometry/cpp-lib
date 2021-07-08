#ifndef __CAR_LINEAR_HPP__
#define __CAR_LINEAR_HPP__
namespace d{

template<typename T>
struct coord {
    T *d;
    long unsigned int dim;
    //coord(int dim, T val=0.0): d(dim, val), dim(dim) {}
    coord(di dim, T val=0.0): dim(dim) {
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
    coord(initializer_list<T> l): dim{l.size()} {
        //printf("init %p\n", this);
        //d=(T *)calloc(dim, sizeof(T));
        d=new T[dim];
        memcpy(d, l.begin(), sizeof(T)*dim);
        //std::copy(l.begin(), l.end(), d);
    }
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
    coord(coord<T> &&other) noexcept: d(std::exchange(other.d, nullptr)), dim(std::exchange(other.dim,(di)0)) {}
    coord& operator=(const coord<T> &other) {
        //printf("move ro3");
        if (this == &other) return *this;
        dim=other.dim;
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
            res+=pow(this->d[i],2.0);
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
    coord<double> round(int digits=0) const {
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
        for(auto &i:res.d) ans+=i;
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
    friend ostream& operator<<(ostream& os, const coord<T> &crd) {
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
    friend coord<T> operator*(coord<T> lhs, const T &r) { return lhs*=r; }
    friend coord<T> operator/(coord<T> lhs, const T &r) { return lhs/=r; }
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

template<typename M>
struct matrix {
    M** d;
    di x, y;
    matrix(di dimX, di dimY): x(dimX), y(dimY) {
        d=new M*[dimX];
        for(di i=0; i<dimX; i++) d[i]=new M[dimY];
    }
    ~matrix() {
        for(di i=0; i<x; i++) delete[](d[i]);
        delete[]d;
    }
    matrix(const matrix<M> &other): x(other.x), y(other.y) {
        //printf("copy ro3");
        d=new M*[x];
        for(di i=0; i<x; i++) d[i]=new M[y];
        for(di i=0; i<x; i++) memcpy(d[i], other.d[i], sizeof(M)*y);
    }
    //coord(coord<M> &&other) noexcept: d(std::exchange(other.d, nullptr)), dim(std::exchange(other.dim,(di)0)) {}
    matrix& operator=(const matrix<M> &other) {
        //printf("move ro3");
        if (this == &other) return *this;
        x=other.x;
        y=other.y;
        d=new M*[x];
        for(di i=0; i<x; i++) d[i]=new M[y];
        for(di i=0; i<x; i++) memcpy(d[i], other.d[i], sizeof(M)*y);
    }
    matrix& operator=(matrix<M> &&other) noexcept {
        swap(x, other.x);
        swap(y, other.y);
        swap(d, other.d);
        return *this;
    }
    template<typename F> M* operator[](F i) { return d[i]; };
    template<typename F> M* operator[](F i) const { return d[i]; };
    friend ostream& operator<<(ostream& os, matrix<M> &crd) {
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
    void print(int precision=15) {
        printf("[%.*lf", precision, d[0][0]);
        for(di i=1;i<x;i++) {
            printf(", %.*lf", precision, d[i][0]);
        }
        printf("]");
        for(di r=1; r<y; r++) {
            printf("\n[%.*lf", precision, d[0][r]);
            for(di i=1;i<x;i++) {
                printf(", %.*lf", precision, d[i][r]);
            }
            printf("]");
        }
        return;
    }
    friend matrix<M> operator*(matrix<M> lhs, matrix<M> rhs) {
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
    coord<M> toCoord() {
        coord<M> res(y);
        for(di i=0; i<y; i++) res[i]=d[0][i];
        return res;
    }
    friend coord<M> operator*(const matrix<M> lhs, coord<M> rhs) {
        coord<M> res(lhs.y, (M)0);
        for(di i=0; i<res.dim; i++) {
            for(di j=0; j<res.dim; j++) res[i]+=lhs[j][i]*rhs[j];
        }
        return res;
    }
    static matrix<M> I(di s) {
        matrix<M> res(s, s);
        for(di i=0; i<s; i++) res[i][i]=1;
        return res;
    }
    static matrix<M> R(double theta) {
        matrix<M> res(2, 2);
        res[0][0]=cos(theta);
        res[1][0]=-sin(theta);
        res[0][1]=sin(theta);
        res[1][1]=cos(theta);
        return res;
    }
    static matrix<M> Rx(double theta) {
        matrix<M> res(3, 3);
        M   a[3]={1, 0, 0},
            b[3]={0, cos(theta), sin(theta)},
            c[3]={0, -sin(theta), cos(theta)};
        memcpy(res[0], a, sizeof(M)*3);
        memcpy(res[1], b, sizeof(M)*3);
        memcpy(res[2], c, sizeof(M)*3);
        return res;
    }
    static matrix<M> Ry(double theta) {
        matrix<M> res(3, 3);
        M   a[3]={cos(theta), 0, -sin(theta)},
            b[3]={0, 1, 0},
            c[3]={sin(theta), 0, cos(theta)};
        memcpy(res[0], a, sizeof(M)*3);
        memcpy(res[1], b, sizeof(M)*3);
        memcpy(res[2], c, sizeof(M)*3);
        return res;
    }
    static matrix<M> Rz(double theta) {
        matrix<M> res(3, 3);
        M   a[3]={cos(theta), sin(theta), 0},
            b[3]={-sin(theta), cos(theta), 0},
            c[3]={0, 0, 1};
        memcpy(res[0], a, sizeof(M)*3);
        memcpy(res[1], b, sizeof(M)*3);
        memcpy(res[2], c, sizeof(M)*3);
        return res;
    }
};

}
#endif
