#ifndef UNNAMING_GAME_SRC_FOV_SHADOWCASTING_H
#define UNNAMING_GAME_SRC_FOV_SHADOWCASTING_H
/**
 * Adapted from: FOV using recursive shadowcasting
 * http://www.roguebasin.com/index.php?title=FOV_using_recursive_shadowcasting
 */
#include <functional>
#include "fraction.h"
#include "../Map/Map.h"
class FunctorShadowCasting final {
  typedef Fraction<int32_t> FractionType;
 public:
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
                 FractionType start, FractionType end, const int8_t mult[4]);
  std::function<bool(const Point&)> IsValid;
  std::function<void(const Point&)> SetViewable;
  std::function<int32_t(const Point&)> GetCost;
};
#endif  // SRC_FOV_SHADOWCASTING_H
