namespace d::numerical::rk4 {
    template<typename C>
        C run(C cur, &f, const double tt) {
            constexpr log=d::dyn::Loggable<C>;
            int loopTimes=(int)std::ceil(tt/d::numerical::rk4::h);
            if constexpr(log) {
                static_assert(cur.log==nullptr, "Log of d::dyn::mono in d::numerical::rk4::run() isn't empty");
                cur.log=(C*)malloc(sizeof(C)*(loopTimes+1));
            }
            double h=tt/((double)loopTimes), hh=h/2;
            for(int i=0; i<=loopTimes; i++) {
                k1=f(cur.pos);
                cur.pos+=d::coord<C>({hh, k1*hh});
                k2=f(cur.pos);
                cur.t+=h;
                if constexpr(log) cur.log[i]=cur;
            }
        }
    template<typename C> mono<C> run(const mono<C>& x0, &f, const double s, const double t) { return run(x0, f, t-s); }
    template<typename C> coord<C> run(const coord<C>& x0, &f, const double s, const double t) { return run(x0, f, t-s); }
    // Perhaps a duplicated version of the loop in run() could be made seperately.
    template<typename C> d::dyn::mono<C> next(d::dyn::mono
}
