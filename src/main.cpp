#include <iostream>
#include "enbodiedapp.h"
#include "taylor.h"

int main(int argc, char* argv[]) {
	EnbodiedApp app;

	for (int i = 1; i < argc; i++)
		std::cout << i << " " << argv[i] << std::endl;

	Taylor tay(5);

	tay.setDerivative(0, 0);
	tay.setDerivative(1, 1);
	tay.setDerivative(2, 0);
	tay.setDerivative(3, -1);
	tay.setDerivative(4, 0);
	tay.setDerivative(5, 1);
	tay.setDerivative(6, 0);
	tay.setDerivative(7, -1);
	tay.setDerivative(8, 0);
	tay.setDerivative(9, 1);
	tay.setDerivative(10, 0);
	tay.setDerivative(11, -1);

	for (double i = -4; i <= 4; i += 0.1)
		std::cout << i << ": " << tay.Calculate(i) << std::endl;
	return app.OnExecute();
}
