#include "taylor.h"

Taylor::Taylor(unsigned int size) {
	Init(size, 0);
}

Taylor::Taylor(unsigned int size, double init_position) {
	Init(size, init_position);
}

Taylor::Taylor() {
	Init(0, 0);
}

Taylor::Taylor(const Taylor &other) {
	if (this != &other) {
		Init(other.getSize(), other.getPosition());
		for (unsigned int i = 0; i < this->arrsize; i++)
			this->derivatives[i] = other.getDerivative(i);
	}
}

Taylor& Taylor::operator=(const Taylor& other) {
	if (this != &other) {
		// Note that if this is not empty, will overwrite
		Init(other.getSize(), other.getPosition());
		for (unsigned int i = 0; i < this->arrsize; i++)
			this->derivatives[i] = other.getDerivative(i);
	}
	return *this;
}

Taylor::~Taylor() {
	delete[] derivatives;
}

void Taylor::setDerivative(unsigned int index, double value) {
	if (index >= arrsize)
		resize(index);
	derivatives[index] = value;
}

void Taylor::resize(unsigned int newsize) {
	unsigned int newarrsize = newsize + 1;
	double * ndivs = new double[newarrsize];
	for (unsigned int i = 0; i < newarrsize; i++)
		ndivs[i] = this->getDerivative(i);
	delete[] derivatives;
	derivatives = ndivs;
	arrsize = newarrsize;
}

void Taylor::Init(unsigned int size, double a_value) {
	if (derivatives != NULL)
		delete[] derivatives;
	arrsize = size + 1;
	derivatives = new double[arrsize];

	for (unsigned int i = 0; i < arrsize; i++)
		derivatives[i] = 0;

	position = a_value;

}

double Taylor::Calculate(double x) const {
	return this->Calculate(x, this->arrsize - 1);
}

double Taylor::Calculate(double x, int components) const {
	double base = getDerivative(0);
	double delta = x - position;
	double powc = 1;
	unsigned long faccounter = 1;
	for (unsigned int i = 1; i <= components; i++) {
		faccounter *= i;
		powc *= delta;
		base += (getDerivative(i) / faccounter) * powc;
	}

	return base;

}
