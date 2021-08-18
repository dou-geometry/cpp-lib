#include<handle.hh>

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
            default:
                return "No Signal Received";
        }
    }
}

int main() {
    signal(SIGTERM, d::signal::handler);
    signal(SIGUSR1, d::signal::handler);
    signal(SIGUSR2, d::signal::handler);
    signal(SIGHUP, d::signal::handler);
    std::cout << ::getpid() << std::endl;
    sleep(4);
    std::cout << pt() << std::endl;
    return 0;
}
