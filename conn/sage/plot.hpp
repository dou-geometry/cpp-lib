#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__

#include"../../cls.hpp"
#include"./settings.hpp"
namespace d { namespace conn { namespace sage {

void plot(field& f, settings::files info) {}
template<typename D> void point(Karabinerhaken<coord<D>>& pts, settings::files info) {}
template<typename D> void line(Karabinerhaken<coord<D>>& pts, settings::files info) {}


}}}
#endif
