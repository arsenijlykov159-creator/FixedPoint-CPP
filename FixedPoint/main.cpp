#include <iostream>
#include "FixedPoint.h"



int main() {

	FixedPoint<2> a{ 0.156 };

	std::cout << a << '\n';

	return 0;
}