#include <iostream>
#include "enbodiedapp.h"

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc; i++)
		std::cout << i << " " << argv[i] << std::endl;
	std::cout << "Test" << std::endl;
	return 0;
}
