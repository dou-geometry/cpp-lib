#include"./sighandle.hh"
volatile sig_atomic_t d::signal::SIGTERMcaught=0;
volatile sig_atomic_t d::signal::SIGUSR1caught=0;
volatile sig_atomic_t d::signal::SIGUSR2caught=0;
void d::signal::signalHandler(int signum) {
    switch(signum) {
        case SIGTERM:
            d::signal::SIGTERMcaught=1;
            break;
        default:
            break;
    }
}
