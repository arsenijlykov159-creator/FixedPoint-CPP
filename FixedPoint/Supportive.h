#if !defined(SUPPORTIVE_H)
#define SUPPORTIVE_H

#include <iostream>

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



#endif