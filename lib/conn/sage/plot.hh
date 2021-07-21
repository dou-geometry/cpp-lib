#include"../../cls.hh"
#include"./settings.hh"
#include"../bash/stdout.hh"
#include"../../dyn/mono.hh"
#include<string>
#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__

namespace d::conn::sage {
	std::string plot(cov&, settings::files&);
	template<typename D> std::string point(Karabinerhaken<d::coord<D>>&, settings::files&);
	template<typename D> std::string line(Karabinerhaken<d::coord<D>>&, settings::files&);
    template<typename D> std::string anime(d::dyn::mono<D>&, settings::files&);
}
#endif
