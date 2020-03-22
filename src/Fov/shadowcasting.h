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
  typedef Fraction<int> IntFraction;
  inline FunctorShadowCasting& SetFunction_IsValid(
      const std::function<bool(const MapPoint&)>& func) {
    IsValid = func;
    return *this;
  }
  inline FunctorShadowCasting& SetFunction_SetViewable(
      const std::function<void(const MapPoint&)>& func) {
    SetViewable = func;
    return *this;
  }
  inline FunctorShadowCasting& SetFunction_GetCost(
      const std::function<int(const MapPoint&)>& func) {
    GetCost = func;
    return *this;
  }
  // Do ShadowCasting
  void operator()(const MapPoint&, const size_t&);

 private:
  void CastLight(const MapPoint&, const size_t&, const int&,
                 IntFraction, IntFraction, const int[4]);
  std::function<bool(const MapPoint&)> IsValid;
  std::function<void(const MapPoint&)> SetViewable;
  std::function<int(const MapPoint&)> GetCost;
};
#endif  // UNNAMING_GAME_SRC_FOV_SHADOWCASTING_H_
