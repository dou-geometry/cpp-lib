#include"../include/conn/bash/stdout.hpp"
#include<string>
#include<iostream>

int main() {
	std::string  o=d::conn::bash::exec("ls");
	std::cout << o << std::endl;
	return 0;
}
