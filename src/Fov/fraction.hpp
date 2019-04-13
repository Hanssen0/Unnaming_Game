#ifndef UNNAMING_GAME_SRC_FOV_FRACTION_HPP_
#define UNNAMING_GAME_SRC_FOV_FRACTION_HPP_

#include <stdint.h>

namespace number {

template <typename T = int32_t>
struct Fraction {
 public:
  T num, den;

 public:
  inline Fraction &Reduce();

 public:
  inline Fraction &operator=(const Fraction &x);
  inline Fraction &operator=(const T &x);

 public:
  inline Fraction &operator+=(const Fraction &x);
  inline Fraction &operator-=(const Fraction &x);
  inline Fraction &operator*=(const Fraction &x);
  inline Fraction &operator/=(const Fraction &x);

  inline Fraction &operator+=(const T &x);
  inline Fraction &operator-=(const T &x);
  inline Fraction &operator*=(const T &x);
  inline Fraction &operator/=(const T &x);

 public:
  inline Fraction operator+(const Fraction &x) const;
  inline Fraction operator-(const Fraction &x) const;
  inline Fraction operator*(const Fraction &x) const;
  inline Fraction operator/(const Fraction &x) const;

  inline Fraction operator+(const T &x) const;
  inline Fraction operator-(const T &x) const;
  inline Fraction operator*(const T &x) const;
  inline Fraction operator/(const T &x) const;

 public:
  inline bool operator<(const Fraction &x) const;
  inline bool operator>(const Fraction &x) const;
  inline bool operator==(const Fraction &x) const;
  inline bool operator!=(const Fraction &x) const;
  inline bool operator<=(const Fraction &x) const;
  inline bool operator>=(const Fraction &x) const;

  inline bool operator<(const T &x) const;
  inline bool operator>(const T &x) const;
  inline bool operator==(const T &x) const;
  inline bool operator!=(const T &x) const;
  inline bool operator<=(const T &x) const;
  inline bool operator>=(const T &x) const;

 public:
  inline Fraction(const T &num_ = 0, const T &den_ = 1)
      : num(num_), den(den_) {}

  template <typename TT>
  inline operator TT() const {
    return den == 0 ? 0 : static_cast<TT>(num) / den;
  }
};

template <typename T>
inline Fraction<T> &Fraction<T>::Reduce() {
  T x = (num < 0 ? -num : num), y = (den < 0 ? -den : den);
  while (y != 0) {  // x = Gcd(x, y)
    x %= y;
    x ^= y, y ^= x, x ^= y;  // Swap(x, y)
  }
  if (x != 0) {
    num /= x, den /= x;
  }
  if (den < 0) {
    num = -num, den = -den;
  }
  return *this;
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator=(const Fraction &x) {
  num = x.num;
  den = x.den;
  return *this;
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator=(const T &x) {
  num = x;
  den = 1;
  return *this;
}

template <typename T>
inline Fraction<T> Fraction<T>::operator+(const Fraction &x) const {
  return Fraction(num * x.den + x.num * den, den * x.den);
}

template <typename T>
inline Fraction<T> Fraction<T>::operator-(const Fraction &x) const {
  return Fraction(num * x.den - x.num * den, den * x.den);
}

template <typename T>
inline Fraction<T> Fraction<T>::operator*(const Fraction &x) const {
  return Fraction(num * x.num, den * x.den);
}

template <typename T>
inline Fraction<T> Fraction<T>::operator/(const Fraction &x) const {
  return Fraction(num * x.den, den * x.num);
}

template <typename T>
inline Fraction<T> Fraction<T>::operator+(const T &x) const {
  return Fraction<T>(num + x * den, 1);
}

template <typename T>
inline Fraction<T> Fraction<T>::operator-(const T &x) const {
  return Fraction<T>(num - x * den, 1);
}

template <typename T>
inline Fraction<T> Fraction<T>::operator*(const T &x) const {
  return Fraction<T>(num * x, den);
}

template <typename T>
inline Fraction<T> Fraction<T>::operator/(const T &x) const {
  return Fraction<T>(num, den * x);
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator+=(const Fraction &x) {
  num = num * x.den + x.num * den;
  den *= x.den;
  return *this;
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator-=(const Fraction &x) {
  num = num * x.den - x.num * den;
  den *= x.den;
  return *this;
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator*=(const Fraction &x) {
  num *= x.num;
  den *= x.den;
  return *this;
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator/=(const Fraction &x) {
  num *= x.den;
  den *= x.num;
  return *this;
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator+=(const T &x) {
  num += x * den;
  return *this;
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator-=(const T &x) {
  num -= x * den;
  return *this;
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator*=(const T &x) {
  num *= x;
  return *this;
}

template <typename T>
inline Fraction<T> &Fraction<T>::operator/=(const T &x) {
  den *= x;
  return *this;
}

template <typename T>
inline bool Fraction<T>::operator<(const Fraction &x) const {
  return (x.den * den > 0 ? num * x.den < x.num * den
                          : num * x.den > x.num * den);
}

template <typename T>
inline bool Fraction<T>::operator>(const Fraction &x) const {
  return (x.den * den > 0 ? num * x.den > x.num * den
                          : num * x.den < x.num * den);
}

template <typename T>
inline bool Fraction<T>::operator==(const Fraction &x) const {
  return num * x.den == x.num * den;
}

template <typename T>
inline bool Fraction<T>::operator!=(const Fraction &x) const {
  return num * x.den != x.num * den;
}

template <typename T>
inline bool Fraction<T>::operator<=(const Fraction &x) const {
  return (x.den * den > 0 ? num * x.den <= x.num * den
                          : num * x.den >= x.num * den);
}

template <typename T>
inline bool Fraction<T>::operator>=(const Fraction &x) const {
  return (x.den * den > 0 ? num * x.den >= x.num * den
                          : num * x.den <= x.num * den);
}

template <typename T>
inline bool Fraction<T>::operator<(const T &x) const {
  return (den > 0 ? num < x * den : num > x * den);
}

template <typename T>
inline bool Fraction<T>::operator>(const T &x) const {
  return (den > 0 ? num > x * den : num < x * den);
}

template <typename T>
inline bool Fraction<T>::operator==(const T &x) const {
  return num == x * den;
}

template <typename T>
inline bool Fraction<T>::operator!=(const T &x) const {
  return num != x * den;
}

template <typename T>
inline bool Fraction<T>::operator<=(const T &x) const {
  return (den > 0 ? num <= x * den : num >= x * den);
}

template <typename T>
inline bool Fraction<T>::operator>=(const T &x) const {
  return (den > 0 ? num >= x * den : num <= x * den);
}

};  // namespace number

#endif  // UNNAMING_GAME_SRC_FOV_FRACTION_HPP_
