//Rational.cpp
#include "Rational.h"
using namespace std;

Rational::Rational()
: numerator(0), denominator(1) {}

Rational::Rational(int val)
: numerator(val), denominator(1) {}

Rational::Rational(int numerator_in, int denominator_in)
: numerator(numerator_in), denominator(denominator_in) {

	if (numerator != 0 && denominator != 0){

		int gcd = 1;
		int temp = 0;
		int d = denominator, n = numerator;
		if (d < n) {
			temp = d;
			d = n;
			n = temp;
		}
		while (n != 0) {
			temp = d % n;
			d = n;
			n = temp;
		}
		gcd = d;

		numerator /= gcd;
		denominator /= gcd;
	}

	if (denominator < 0) {
		denominator *= -1;
		numerator *= -1;
	}


	if (numerator == 0 && denominator != 0) denominator = 1;
	if (numerator > 0 && denominator == 0) numerator = 1;
	if (numerator < 0 && denominator == 0) numerator = -1;
}

int Rational::get_numerator() const {
	return numerator;
}

int Rational::get_denominator() const {
	return denominator;
}

ostream& operator<<(std::ostream& os, const Rational& obj) {
	if (obj.get_denominator() == 1) os << obj.get_numerator();
	else {
		os << obj.get_numerator() << "/" << obj.get_denominator();
	}
	return os;
}

Rational operator+(const Rational &lhs, const Rational &rhs) {
	int a = lhs.get_numerator(), b = lhs.get_denominator();
	int c = rhs.get_numerator(), d = rhs.get_denominator();

	return Rational((a * d + b * c), (b * d));
}

Rational operator-(const Rational &lhs, const Rational &rhs) {
	int a = lhs.get_numerator(), b = lhs.get_denominator();
	int c = rhs.get_numerator(), d = rhs.get_denominator();

	return Rational((a * d - b * c), (b * d));
}

Rational operator*(const Rational &lhs, const Rational &rhs) {
	int a = lhs.get_numerator(), b = lhs.get_denominator();
	int c = rhs.get_numerator(), d = rhs.get_denominator();

	return Rational((a * c), (b * d));	
}

Rational operator/(const Rational &lhs, const Rational &rhs) {
	int a = lhs.get_numerator(), b = lhs.get_denominator();
	int c = rhs.get_numerator(), d = rhs.get_denominator();

	return Rational((a * d), (b * c));	
}

bool operator==(const Rational &lhs, const Rational &rhs) {
	return lhs.get_numerator() == rhs.get_numerator() &&
	lhs.get_denominator() == rhs.get_denominator();
}


