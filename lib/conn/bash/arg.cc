#include"../../../include/conn/bash/arg.hpp"

template<typename U>
void d::conn::bash::arg::setup(int &argc, char **argv, opts m, std::convertible_to<char> U x, std::convertible_to<U> auto ... Ts) {
    int c = getopt(argc, argv, (char*)m);
    m[c]=optarg;
    return d::conn::bash::arg::setup(argc, argv, m, Ts...);
};
void d::conn::bash::arg::setup(int &argc, chcar **argv) {
    for(int index=optind; index<argc; index++)
        printf("Non-option argument %s\n", argv[index]);
    return;
}
