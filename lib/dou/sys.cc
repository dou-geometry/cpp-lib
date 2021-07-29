#include"./sys.hh"

namespace d::dou::compact {
    sys::sys(double leftBoundary, double rightBoundary) { //bl, tr as template?
        // メルセンヌ・ツイスター法による擬似乱数生成器を、
        // ハードウェア乱数をシードにして初期化
        std::random_device seed_gen;
        std::mt19937 engine(seed_gen());

        // 一様実数分布
        // [-1.0, 1.0)の値の範囲で、等確率に実数を生成する
        std::uniform_real_distribution<> dist1(leftBoundary, rightBoundary);
        for(di i=0; i<amount; ++i) {
            //d[i].t=0.0;
            for(di j=0; j<dimension; ++j) {
                d[i][0][j]=dist1(engine); // Position
                d[i][1][j]=dist1(engine); // Velocity
            }
        }
    }
    bool sys::stable() {
    }
}
