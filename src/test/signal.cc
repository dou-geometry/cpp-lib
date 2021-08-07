#include"../../lib/signal/handle.hh"

#include<iostream>

void pt() {
    switch d::signal::last {
        case SIGTERM:
            std::cout << "Term" << std::endl;
            break;
        default:
            std::cout << "nothing" << std::endl;
            break;
    }
}
