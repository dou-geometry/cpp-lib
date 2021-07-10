#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__

#include"../../cls.hpp"
#include"./settings.hpp"
#include"../bash/stdout.hpp"
//namespace d { namespace conn { namespace sage {
namespace d::conn::sage {
    void plot(conn::sage::settings::files&);
    template<typename D> void plot(field<D>&, settings::files&);
    template<typename D> void point(Karabinerhaken<coord<D>>&, settings::files&);
    template<typename D> void line(Karabinerhaken<coord<D>>&, settings::files&);
}}}
#endif
