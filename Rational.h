#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <cstdlib>
#include <cassert>


class Rational {

 private:
  int numerator;
  int denominator;

 public:
  // EFFECTS: Constructor for rational number that is equivalent to integer 0.
  Rational();

  // EFFECTS: Constructor for rational number that is equivalent
  // to integer val.
  Rational(int val);

  // EFFECTS: Constructor for a rational number that is equivalent to
  // numerator_in/denominator_in.
  // Remember to ensure the Invariants.
  Rational(int numerator_in, int denominator_in);

  // EFFECTS: Returns numerator that is consistent with the invariants.
  int get_numerator() const;

  // EFFECTS: Returns denominator that is consistent with the invariants.
  // after eliminating any common factors. See invariants.
  int get_denominator() const;
};

std::ostream& operator<<(std::ostream& os, const Rational& obj);

// EFFECTS: Returns a rational number equivalent to lhs + rhs.
// Note that (a/b + c/d) is algebraically equivalent to (ad+bc)/bd.
Rational operator+(const Rational &lhs, const Rational &rhs);

// EFFECTS: Returns a rational number equivalent to lhs - rhs.
//   Note that (a/b + c/d) is algebraically
// equivalent to (ad-bc)/bd.
Rational operator-(const Rational &lhs, const Rational &rhs);

// EFFECTS: Returns a rational number equivalent to lhs * rhs.
//   Note that (a/b * c/d) is algebraically
// equivalent to ac/bd.
Rational operator*(const Rational &lhs, const Rational &rhs);

// EFFECTS: Returns a rational number equivalent to lhs / rhs.
//   Note that (a/b / c/d) is algebraically
// equivalent to ad/bc.
Rational operator/(const Rational &lhs, const Rational &rhs);

// EFFECTS: Returns true if the two rational numbers are equal.  Otherwise,
//   returns false.
bool operator==(const Rational &lhs, const Rational &rhs);

#endif //RATIONAL_H
