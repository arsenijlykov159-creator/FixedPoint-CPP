#if !defined(FIXEDPOINT_H)
#define FIXEDPOINT_H

#include <iostream>
#include <iomanip>
#include <cstdint>
#include <cassert>
#include <type_traits>
#include <cmath>
#include <limits>


template <std::size_t N>
class FixedPoint {
public:
	static_assert(N < 7 && "Слишком большая точность!");
	using Fract_Type = std::conditional_t<(N <= 2), std::int8_t, std::conditional_t<(N > 2 && N <= 4), std::int16_t, std::int32_t>>;
	using Int_Type = std::conditional_t<(N <= 4), std::int16_t, std::int32_t>;

private:
	Int_Type m_int_part{};
	Fract_Type m_fract_part{};
	static constexpr Fract_Type m_multiplier{ static_cast<Fract_Type>(power<long long>(10, N)) };


	static constexpr double sign(double d) {
		if (d >= 0) return 1;
		else return -1;
	}

	std::pair<double, double> split(double value) {
		double int_part{};
		double fr_part{ std::modf(value, &int_part) };
		return { int_part, fr_part };
	}


public:
	explicit FixedPoint() = default;

	explicit FixedPoint(long long int_part, long long fract_part = 0) {
		if (int_part < 0 || fract_part < 0) {
			if (int_part > 0) int_part *= -1;
			else if (fract_part > 0) fract_part *= -1;
		}

		int_part += fract_part / m_multiplier;
		fract_part %= m_multiplier;

		assert(static_cast<double>(int_part) <= static_cast<double>(std::numeric_limits<Int_Type>::max()));
		assert(static_cast<double>(int_part) >= static_cast<double>(std::numeric_limits<Int_Type>::min()));
		//assert(static_cast<double>(fract_part) <= static_cast<double>(std::numeric_limits<Fract_Type>::max()));
		//assert(static_cast<double>(fract_part) >= static_cast<double>(std::numeric_limits<Fract_Type>::min()));

		m_int_part = static_cast<Int_Type>(int_part);
		m_fract_part = static_cast<Fract_Type>(fract_part);

		//std::cout << *this << '\n';
	}

	explicit FixedPoint(double value) : FixedPoint(static_cast<long long>(split(value).first), static_cast<long long>(std::round(split(value).second* m_multiplier))) {}





	explicit operator double() const { return m_int_part + static_cast<double>(m_fract_part) / m_multiplier; }

	FixedPoint operator-() const {
		return FixedPoint{
			static_cast<Int_Type>(-m_int_part),
			static_cast<Fract_Type>(-m_fract_part)
		};
	}

	FixedPoint& operator+=(const FixedPoint& fp) {
		double temp{ static_cast<double>(*this) + static_cast<double>(fp) };

		*this = FixedPoint{ temp };
		return *this;
	}
	FixedPoint& operator-=(const FixedPoint& fp) {
		*this += -fp;
		return *this;
	}
	FixedPoint& operator*=(const FixedPoint& fp) {
		double temp{ static_cast<double>(*this) * static_cast<double>(fp) };

		*this = FixedPoint{ temp };
		return *this;
	}
	FixedPoint& operator/=(const FixedPoint& fp) {
		assert(static_cast<double>(fp) != 0.0);

		double temp{ static_cast<double>(*this) / static_cast<double>(fp) };

		*this = FixedPoint{ temp };
		return *this;
	}


	friend FixedPoint operator+(const FixedPoint& fp1, const FixedPoint& fp2) {
		auto temp{ fp1 };
		temp += fp2;

		return temp;
	}
	friend FixedPoint operator-(const FixedPoint& fp1, const FixedPoint& fp2) {
		auto temp{ fp1 };
		temp -= fp2;

		return temp;
	}
	friend FixedPoint operator*(const FixedPoint& fp1, const FixedPoint& fp2) {
		auto temp{ fp1 };
		temp *= fp2;

		return temp;
	}
	friend FixedPoint operator/(const FixedPoint& fp1, const FixedPoint& fp2) {
		auto temp{ fp1 };
		temp /= fp2;

		return temp;
	}

	friend bool operator==(const FixedPoint& fp1, const FixedPoint& fp2) {
		return (fp1.m_int_part == fp2.m_int_part && fp1.m_fract_part == fp2.m_fract_part);
	}

	friend std::istream& operator>>(std::istream& in, FixedPoint& fp) {
		double value{};
		std::cin >> value;

		FixedPoint temp{ value };
		fp = temp;

		return in;
	}

	friend std::ostream& operator<<(std::ostream& out, const FixedPoint& fp) {
		if (fp.m_int_part == 0 && fp.m_fract_part < 0) out << '-';
		out << fp.m_int_part << '.' << std::setw(N) << std::setfill('0') << static_cast<std::size_t>(std::abs(fp.m_fract_part));
		return out;
	}

};





#endif