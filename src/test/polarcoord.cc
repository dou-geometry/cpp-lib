#include<oricoord.hh>

int main() {
    d::polarcoord a(1, 0), b(1, d::deg(60));
    std::cout << a << std::endl << b << std::endl;
    return 0;
}
