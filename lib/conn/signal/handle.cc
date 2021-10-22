#include<handle.hh>
volatile sig_atomic_t d::signal::SIGTERMcaught=0;
volatile sig_atomic_t d::signal::SIGUSR1caught=0;
volatile sig_atomic_t d::signal::SIGUSR2caught=0;
volatile sig_atomic_t d::signal::SIGHUPcaught=0;
volatile sig_atomic_t d::signal::last=0;
void d::signal::handler(int signum) {
    d::signal::last=signum;
    switch(signum) {
        case SIGTERM:
            d::signal::SIGTERMcaught=1;
            break;
        case SIGUSR1:
            d::signal::SIGUSR1caught=1;
            break;
        case SIGUSR2:
            d::signal::SIGUSR2caught=1;
            break;
        case SIGHUP:
            d::signal::SIGHUPcaught=1;
            break;
        default:
            break;
    }
}
