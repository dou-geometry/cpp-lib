#include"../../lib/signal/handle.hh"

#include<iostream>
#include <unistd.h>

std::string pt() {
    while(true) {
        switch(d::signal::last) {
            case SIGTERM:
                return "SIGTERM";
            case SIGUSR1:
                return "SIGUSR1";
            case SIGUSR2:
                return "SIGUSR2";
            case SIGHUP:
                return "SIGHUP";
        }
    }
}

int main() {
    signal(SIGTERM, d::signal::signalHandler);
    signal(SIGUSR1, d::signal::signalHandler);
    signal(SIGUSR2, d::signal::signalHandler);
    signal(SIGHUP, d::signal::signalHandler);
    std::cout << ::getpid() << std::endl;
    std::cout << pt() << std::endl;
    return 0;
}
