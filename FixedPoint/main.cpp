#include <iostream>
#include "FixedPoint.h"



template <typename T>
constexpr T power(const T& base, std::size_t exp) {
	if (exp == 0) return 1;
	if (exp == 1) return base;

	T result{ base };

	for (std::size_t i{ 1 }; i < exp; ++i) {
		result *= base;
	}

	return result;
}
















int main() {

	FixedPoint<4> a{ 10000.0 };

	a /= FixedPoint<4>(0.33);

	std::cout << a << '\n';

	return 0;
}