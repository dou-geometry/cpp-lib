#include"../../cls.hpp"
#include"./settings.hpp"
#include"../bash/stdout.hpp"
#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__

namespace d::conn::sage {
	void plot(cov&, settings::files&);
	template<typename D> void point(Karabinerhaken<coord<D>>&, settings::files&);
	template<typename D> void line(Karabinerhaken<coord<D>>&, settings::files&);
}
#endif
