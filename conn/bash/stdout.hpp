#ifndef __CONN_BASH_O__
#define __CONN_BASH_O__
namespace d { namespace conn { namespace bash {

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}
// https://stackoverflow.com/a/478960/8460574

}}}
#endif
