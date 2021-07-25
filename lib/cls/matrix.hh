#ifndef __CAR_LINEAR_MATRIX_HPP__
#define __CAR_LINEAR_MATRIX_HPP__
namespace d {
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
            friend matrix<M> operator*(matrix<M> lhs, const matrix<M>& rhs) {
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
            friend coord<M> operator*(matrix<M> lhs, const coord<M>& rhs) {
                coord<M> res(lhs.y, (M)0);
                for(di i=0; i<res.dim; i++) {
                    for(di j=0; j<res.dim; j++) res[i]+=lhs[j][i]*rhs[j];
                }
                return res;
            }
            template<typename H>
                requires d::coordCarrier<H>
                inline friend H operator*(matrix<M> lhs, H rhs) {
                    for(di i=0; i<rhs.dim; ++i)
                        rhs[i]=lhs*rhs[i];
                    return rhs;
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
