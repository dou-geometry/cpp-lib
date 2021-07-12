<<<<<<< Updated upstream
#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__

#include"../../cls.hpp"
#include"./settings.hpp"
#include"../bash/stdout.hpp"
//namespace d { namespace conn { namespace sage {
namespace d::conn::sage {
=======
#include"../../cls.hpp"
#include"./settings.hpp"
#include"../bash/stdout.hpp"
#ifndef __CONN_SAGE_PLOT__
#define __CONN_SAGE_PLOT__

//namespace d { namespace conn { namespace sage {
namespace d { namespace conn { namespace sage {
>>>>>>> Stashed changes
    void plot(conn::sage::settings::files&);
    template<typename D> void plot(field<D>&, settings::files&);
    template<typename D> void point(Karabinerhaken<coord<D>>&, settings::files&);
    template<typename D> void line(Karabinerhaken<coord<D>>&, settings::files&);
}}}
#endif
