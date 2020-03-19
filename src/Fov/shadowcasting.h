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
#ifndef UNNAMING_GAME_SRC_FOV_SHADOWCASTING_H_
#define UNNAMING_GAME_SRC_FOV_SHADOWCASTING_H_
/**
 * Adapted from: FOV using recursive shadowcasting
 * http://www.roguebasin.com/index.php?title=FOV_using_recursive_shadowcasting
 */
#include <functional>
#include "./fraction.h"
#include "../Map/Map.h"
class FunctorShadowCasting final {
 public:
  typedef Fraction<int32_t> IntFraction;
  inline FunctorShadowCasting& SetFunction_IsValid(
      const std::function<bool(const Point&)>& func) {
    IsValid = func;
    return *this;
  }
  inline FunctorShadowCasting& SetFunction_SetViewable(
      const std::function<void(const Point&)>& func) {
    SetViewable = func;
    return *this;
  }
  inline FunctorShadowCasting& SetFunction_GetCost(
      const std::function<int32_t(const Point&)>& func) {
    GetCost = func;
    return *this;
  }
  /**
   * Do ShadowCasting
   *
   * @param pos: position of Point Lights.
   * @param radius: radius of Point Lights.
   */
  void operator()(const Point& pos, const int32_t& radius);

 private:
  void CastLight(const Point& pos, const int32_t& radius, const int32_t& column,
                 IntFraction start, IntFraction end, const int8_t mult[4]);
  std::function<bool(const Point&)> IsValid;
  std::function<void(const Point&)> SetViewable;
  std::function<int32_t(const Point&)> GetCost;
};
#endif  // UNNAMING_GAME_SRC_FOV_SHADOWCASTING_H_
