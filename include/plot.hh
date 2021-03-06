#include<cls.hh>
#include<settings.hh>
#include<stdout.hh>
#include<mono.hh>
#include<logIncrPromise.hh>
#include<tracksTime.hh>
#include<animeFormat.hh>
#include<string>
#include<stack>
#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__
#define di long unsigned int
#define ull unsigned long long int
#define ll long long int
namespace d::conn::sage {
    std::string plot(cov&, settings::files<settings::png>&);
    template<typename D, const char *M>
        requires d::logIncrPromise<D> && //currently useless
        d::tracksTime<D> &&
        d::animeFormat<M>
        std::string anime(const D&, settings::files<M>&, di shadowFrames=0);
    template<bool logIncrPromise=false, typename D, const char *M>
        requires d::tracksTime<d::dyn::mono<D, logIncrPromise>>
        std::string plot(const d::dyn::mono<D, logIncrPromise>&, settings::files<M>&);
    std::string cleanup(std::stack<std::string>&);
    //template<typename D> std::string point(Karabinerhaken<d::coord<D>>&, settings::files&);
    //template<typename D> std::string line(Karabinerhaken<d::coord<D>>&, settings::files&);
}
#include"./plot.tt"
#endif
