#include"../../cls.hpp"
#include"./settings.hpp"
#include"../bash/stdout.hpp"
#include<string>
#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__

namespace d::conn::sage {
	std::string plot(cov&, settings::files&);
	template<typename D> std::string point(Karabinerhaken<coord<D>>&, settings::files&);
	template<typename D> std::string line(Karabinerhaken<coord<D>>&, settings::files&);
}
#endif
