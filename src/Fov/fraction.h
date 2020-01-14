#ifndef UNNAMING_GAME_SRC_FOV_FRACTION_H_
#define UNNAMING_GAME_SRC_FOV_FRACTION_H_
#include <cstdint>
#include <cmath>
#include <algorithm>
#ifndef NDEBUG
  #include <iostream>
#endif
template <typename T>
class Fraction {
 public:
  T number_, denominator_;
  void Reduce();
  template <typename TT>
  inline void operator=(const Fraction<TT>& fraction);
  inline void operator=(const T& x);
  inline Fraction operator+(const Fraction& fraction) const;
  inline Fraction operator-(const Fraction& fraction) const;
  inline bool operator>(const Fraction& fraction) const;
  inline bool operator<(const Fraction& fraction) const;
  inline bool operator>=(const Fraction& fraction) const;
  inline bool operator<=(const Fraction& fraction) const;
  inline Fraction(const T& number, const T& denominator = 1)
      : number_(number), denominator_(denominator) {}
  template <typename TT>
  inline operator TT() const;
#ifndef NDEBUG
  inline void Print() const {
    std::cout << number_ << "/" << denominator_;
  }
#endif
};
template <typename T>
void Fraction<T>::Reduce() {
  T x = std::abs(number_), y = std::abs(denominator_);
  while (y != 0) {  // x = Gcd(x, y)
    x %= y;
    std::swap(x, y);
  }
  if (x != 0) number_ /= x, denominator_ /= x;
  if (denominator_ < 0) number_ = -number_, denominator_ = -denominator_;
}
template <typename T>
template <typename TT>
inline void Fraction<T>::operator=(const Fraction<TT>& fraction) {
  number_ = fraction.number_;
  denominator_ = fraction.denominator_;
}
template <typename T>
inline void Fraction<T>::operator=(const T& number) {
  number_ = number;
  denominator_ = 1;
}
template <typename T>
inline Fraction<T> Fraction<T>::operator+(const Fraction& fraction) const {
  return Fraction(number_*fraction.denominator_ +
                  fraction.number_*denominator_,
                  denominator_*fraction.denominator_);
  // a/b + c/d = (ad + cb)/bd
}
template <typename T>
inline Fraction<T> Fraction<T>::operator-(const Fraction& fraction) const {
  return Fraction(number_*fraction.denominator_ -
                  fraction.number_*denominator_,
                  denominator_*fraction.denominator_);
  // a/b - c/d = (ad - cb)/bd
}
template <typename T>
inline bool Fraction<T>::operator<(const Fraction& fraction) const {
  return (fraction.denominator_*denominator_ > 0 ?
          number_*fraction.denominator_ < fraction.number_*denominator_ :
          number_*fraction.denominator_ > fraction.number_*denominator_);
  // a/b < c/d :
  // ad < cb (same sign)
  // ad > cb (different sign)
}
template <typename T>
inline bool Fraction<T>::operator>(const Fraction& fraction) const {
  return (fraction.denominator_*denominator_ > 0 ?
          number_*fraction.denominator_ > fraction.number_*denominator_ :
          number_*fraction.denominator_ < fraction.number_*denominator_);
  // a/b > c/d :
  // ad > cb (same sign)
  // ad < cb (different sign)
}
template <typename T>
inline bool Fraction<T>::operator<=(const Fraction& fraction) const {
  return (fraction.denominator_*denominator_ > 0 ?
          number_*fraction.denominator_ <= fraction.number_*denominator_ :
          number_*fraction.denominator_ >= fraction.number_*denominator_);
  // a/b <= c/d :
  // ad <= cb (same sign)
  // ad >= cb (different sign)
}
template <typename T>
inline bool Fraction<T>::operator>=(const Fraction& fraction) const {
  return (fraction.denominator_*denominator_ > 0 ?
          number_*fraction.denominator_ >= fraction.number_*denominator_ :
          number_*fraction.denominator_ <= fraction.number_*denominator_);
  // a/b >= c/d :
  // ad >= cb (same sign)
  // ad <= cb (different sign)
}
template <typename T>
template <typename TT>
inline Fraction<T>::operator TT() const {
  return denominator_ == 0 ? 0 : static_cast<TT>(number_)/denominator_;
}
#endif  // UNNAMING_GAME_SRC_FOV_FRACTION_H_
