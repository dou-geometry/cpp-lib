#pragma once
#define di long unsigned int
#include<random>
#include"../conn/sage/settings.hh"
#include"./mono.hh"
#include<iostream>

/*
namespace d::dou {
    struct sys2d { //VLA version
        d::dou::mono<double>* d;
        di amount;
        const di dim=2;
        sys2d() = delete;
        sys2d(di cnt, double leftBoundary=-2., double rightBoundary=2.): amount(cnt) {
            //d=new d::dou::mono<double>[amount];
            d=(d::dou::mono<double>*)malloc(sizeof(d::dou::mono<double>)*amount);
            // メルセンヌ・ツイスター法による擬似乱数生成器を、
            // ハードウェア乱数をシードにして初期化
            std::random_device seed_gen;
            std::mt19937 engine(seed_gen());

            // 一様実数分布
            // [-1.0, 1.0)の値の範囲で、等確率に実数を生成する
            std::uniform_real_distribution<> dist1(leftBoundary, rightBoundary);
            for(di i=0; i<amount; ++i) {
                new(d+i)d::dou::mono((di)2, 0.0, d::coord<double>({dist1(engine), dist1(engine)}), d::coord<double>({dist1(engine), dist1(engine)}));
            }
        }
        ~sys2d() {
            //delete[]d;
            for(di i=0; i<amount; ++i)
                d[i].~mono();
            free(d);
        }
    };
}
*/

namespace d::dou::compact { // Focus
    template<di dimension=2, di particles=1224>
    struct sys {
        d::dou::compact::mono<double, 2ul, dimension, true> d[particles];
        static constexpr di amount=particles;
        sys(double leftBoundary=-2., double rightBoundary=2.); //bl, tr as template?
        ~sys() {}
        d::dou::compact::mono<double, 2ul, dimension, true> operator[](int i) const { return this->d[i]; }
        d::dou::compact::mono<double, 2ul, dimension, true>& operator[](int i) { return this->d[i]; }
        d::dou::compact::mono<double, 2ul, dimension, true>& operator()(const d::compact::coord<double, dimension>&);
        d::dou::compact::mono<double, 2ul, dimension, true> operator()(const d::compact::coord<double, dimension>&) const;
        d::compact::coord<double, dimension> existence(int i) const;
        d::compact::coord<double, dimension> existence(const d::compact::coord<double, dimension>& i) { return this->existence((*this)(i)); }
        bool stable();
        bool confined();
        template<bool background=false> std::string plot(d::conn::sage::settings::files<d::conn::sage::settings::gif>&);
        friend std::ostream& operator<<(std::ostream& os, const d::dou::compact::sys<dimension, particles>& s) {
            for(di i=0; i<particles; ++i)
                os<<s.d[i]<<"\n";
            return os;
        }
    };
}
/*
namespace d::dou::linked {
    struct sys {
        d::Karabinerhaken<d::dou::mono<double>>* d;
        template<typename F> linked& apply(const F& f) {}
    };
}

namespace d::dou::linked::compact {
    template<di dimension=2>
    struct sys {
        di amount=1224;
        d::Karabinerhaken<d::dou::compact::mono<double, 2ul, dimension, true>>* d=nullptr;
        template<typename F> linked& apply(const F& f) {}
        sys(double leftBoundary=-2., double rightBoundary=2.) {
            // メルセンヌ・ツイスター法による擬似乱数生成器を、
            // ハードウェア乱数をシードにして初期化
            std::random_device seed_gen;
            std::mt19937 engine(seed_gen());

            // 一様実数分布
            // [-1.0, 1.0)の値の範囲で、等確率に実数を生成する
            std::uniform_real_distribution<> dist1(leftBoundary, rightBoundary);

            d::dou::compact::mono<double, 2ul, dimension, true> firstItem;
            for(di j=0; j<dimension; ++j) {
                firstItem[0][j]=dist1(engine); // Position
                firstItem[1][j]=dist1(engine); // Velocity
            }

            d::Karabinerhaken<d::dou::compact::mono<double, 2ul, dimension, true>>* cur=new d::Karabinerhaken<d::dou::compact::mono<double, 2ul, dimension, true>>(firstItem);
            this->d=cur;

            for(di i=1; i<amount; ++i) {
                d::dou::compact::mono<double, 2ul, dimension, true> nextItem;
                for(di j=0; j<dimension; ++j) {
                    nextItem[0][j]=dist1(engine); // Position
                    nextItem[1][j]=dist1(engine); // Velocity
                }
                (new d::Karabinerhaken<d::dou::compact::mono<double, 2ul, dimension, true>>(nextItem))->insertAfter(cur);
                cur=cur->tugi;
            }
        }
        ~sys() {
            d.~Karabinerhaken();
        }
    };
}
*/

#include"./sys.tt"
