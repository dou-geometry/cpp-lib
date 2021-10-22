/* Usage:
 * Put following code at top of main()
 * signal(SIGTERM, d::signal::handler);
 * change signal name as you like
 */
#pragma once
#include<signal.h>
namespace d::signal {
    extern volatile sig_atomic_t last;
    extern volatile sig_atomic_t SIGTERMcaught;
    extern volatile sig_atomic_t SIGUSR1caught;
    extern volatile sig_atomic_t SIGUSR2caught;
    extern volatile sig_atomic_t SIGHUPcaught;
    void handler(int);
}
