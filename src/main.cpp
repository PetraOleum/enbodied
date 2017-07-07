#include <iostream>
#include "enbodiedapp.h"
#include "taylor.h"

int main(int argc, char* argv[]) {
	EnbodiedApp app;

	for (int i = 1; i < argc; i++)
		std::cout << i << " " << argv[i] << std::endl;

	return app.OnExecute();
}
