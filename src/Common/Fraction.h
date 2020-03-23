// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_COMMON_FRACTION_H_
#define UNNAMING_GAME_SRC_COMMON_FRACTION_H_
#include <cmath>
#include <utility>
#ifndef NDEBUG
  #include <string>
#endif
template <typename T>
class Fraction {
 public:
  T number_, denominator_;
  inline void Reduce() {
    T x = std::abs(number_), y = std::abs(denominator_);
    while (y != 0) {  // x = Gcd(x, y)
      x %= y;
      std::swap(x, y);
    }
    if (x != 0) number_ /= x, denominator_ /= x;
    if (denominator_ < 0) number_ = -number_, denominator_ = -denominator_;
  }
  template <typename TT>
  inline const Fraction& operator=(const Fraction<TT>& fraction) {
    number_ = fraction.number_;
    denominator_ = fraction.denominator_;
    return *this;
  }
  inline const Fraction& operator=(const T& number) {
    number_ = number;
    denominator_ = 1;
    return *this;
  }
  inline Fraction operator+(const Fraction& fraction) const {
    return Fraction(number_*fraction.denominator_ +
                    fraction.number_*denominator_,
                    denominator_*fraction.denominator_);
    // a/b + c/d = (ad + cb)/bd
  }
  inline Fraction operator-(const Fraction& fraction) const {
    return Fraction(number_*fraction.denominator_ -
                    fraction.number_*denominator_,
                    denominator_*fraction.denominator_);
    // a/b - c/d = (ad - cb)/bd
  }
  inline bool operator>(const Fraction& fraction) const {
    return (fraction.denominator_*denominator_ > 0 ?
            number_*fraction.denominator_ > fraction.number_*denominator_ :
            number_*fraction.denominator_ < fraction.number_*denominator_);
    // a/b > c/d :
    // ad > cb (same sign)
    // ad < cb (different sign)
  }
  inline bool operator<(const Fraction& fraction) const {
    return (fraction.denominator_*denominator_ > 0 ?
            number_*fraction.denominator_ < fraction.number_*denominator_ :
            number_*fraction.denominator_ > fraction.number_*denominator_);
    // a/b < c/d :
    // ad < cb (same sign)
    // ad > cb (different sign)
  }
  inline bool operator>=(const Fraction& fraction) const {
    return (fraction.denominator_*denominator_ > 0 ?
            number_*fraction.denominator_ >= fraction.number_*denominator_ :
            number_*fraction.denominator_ <= fraction.number_*denominator_);
    // a/b >= c/d :
    // ad >= cb (same sign)
    // ad <= cb (different sign)
  }
  inline bool operator<=(const Fraction& fraction) const {
    return (fraction.denominator_*denominator_ > 0 ?
            number_*fraction.denominator_ <= fraction.number_*denominator_ :
            number_*fraction.denominator_ >= fraction.number_*denominator_);
    // a/b <= c/d :
    // ad <= cb (same sign)
    // ad >= cb (different sign)
  }
  inline Fraction(const T& number, const T& denominator = 1) // NOLINT
      : number_(number), denominator_(denominator) {}
  template <typename TT>
  explicit inline operator TT() const {
    return denominator_ == 0 ? 0 : static_cast<TT>(number_)/denominator_;
  }
#ifndef NDEBUG
  inline std::string ToString() const {
    std::string ret = number_;
    return ret + "/" + denominator_;
  }
#endif
};
#endif  // UNNAMING_GAME_SRC_COMMON_FRACTION_H_
