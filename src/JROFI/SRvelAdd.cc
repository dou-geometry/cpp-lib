#include <cstdlib>
#include<IvSR.hh>

int main() {
    /*
    double SvS=0., SvL=0.7, LvM=0.7;
    auto correct=[](double a, double b) { return (a+b)/(1+a*b); };
    std::cout << d::Iv(SvL, LvM)*(LvM)+d::Iv(SvL)*SvL << std::endl << correct(SvL, LvM) << std::endl;
    */
    double I[10000][10000];
    for(di i=0; i<10000; ++i)
        for(di j=0; j<10000; ++j)
            I[i][j]=(1+i*j*1e-8);
    return 0;
}
