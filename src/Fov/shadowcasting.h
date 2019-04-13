#ifndef UNNAMING_GAME_SRC_FOV_SHADOWCASTING_H
#define UNNAMING_GAME_SRC_FOV_SHADOWCASTING_H

/**
 * Adapted from: FOV using recursive shadowcasting
 * http://www.roguebasin.com/index.php?title=FOV_using_recursive_shadowcasting
 */

#include <functional>
#include "fraction.hpp"

namespace fov {

struct Point {
  int32_t x, y;
  Point(const int32_t &_x, const int32_t &_y) : x(_x), y(_y) {}
};

class FunctorShadowCasting final {
  typedef number::Fraction<int32_t> FractionType;

 public:
  inline FunctorShadowCasting &SetFunction_IsValid(
      const std::function<bool(const Point &)> &func) {
    IsValid = func;
    return *this;
  }

  inline FunctorShadowCasting &SetFunction_SetViewable(
      const std::function<void(const Point &)> &func) {
    SetViewable = func;
    return *this;
  }

  inline FunctorShadowCasting &SetFunction_GetCost(
      const std::function<int32_t(const Point &)> &func) {
    GetCost = func;
    return *this;
  }

  /**
   * Do ShadowCasting
   *
   * @param pos: position of Point Lights.
   * @param radius: radius of Point Lights.
   */
  void operator()(const Point &pos, const int32_t &radius);

 private:
  void CastLight(const Point &pos, const int32_t &radius, const int32_t &row,
                 FractionType start, FractionType end, const int8_t mult[4]);

 private:
  std::function<bool(const Point &)> IsValid;
  std::function<void(const Point &)> SetViewable;
  std::function<int32_t(const Point &)> GetCost;

  const int8_t kMult[8][4] = {{-1, 0, 0, -1}, {0, -1, -1, 0}, {0, -1, 1, 0},
                              {-1, 0, 0, 1},  {1, 0, 0, 1},   {0, 1, 1, 0},
                              {0, 1, -1, 0},  {1, 0, 0, -1}};
};

}  // namespace fov

namespace fov {

void FunctorShadowCasting::operator()(const Point &pos, const int32_t &radius) {
  if (IsValid(pos)) {
    for (int i = 0; i < 8; ++i) {
      CastLight(pos, radius, 1, 1.0, 0.0, kMult[i]);
    }
  }
}

void FunctorShadowCasting::CastLight(const Point &pos, const int32_t &radius,
                                     const int32_t &row, FractionType start,
                                     FractionType end, const int8_t mult[4]) {
  // 0 < end < start < 1.0
  if (start > 1) {
    start = 1;
  }
  if (end < 0) {
    end = 0;
  }
  if (start <= end || radius <= 0) {
    return;
  }

  uint64_t radius_squared = static_cast<uint64_t>(radius) * radius;
  for (int32_t j = row; j <= radius; ++j) {
    int32_t dx = -j - 1, dy = -j;
    bool costly = false;
    FractionType new_start = start;

    while (dx++ <= 0) {
      // Translate the dx, dy coordinates into map coordinates.
      Point now_pos(pos.x + dx * mult[0] + dy * mult[1],
                    pos.y + dx * mult[2] + dy * mult[3]);

      // l_slope and r_slope store the slopes of the left and right
      // extremities of the square we're considering.
      FractionType l_slope(dx * 2 - 1, dy * 2 + 1),
          r_slope(dx * 2 + 1, dy * 2 - 1);
      if (start < r_slope) {
        continue;
      } else if (end > l_slope) {
        break;
      }

      if (static_cast<uint64_t>(dx) * dx + static_cast<uint64_t>(dy) * dy >
          radius_squared) {
        continue;
      }

      // Our light beam is touching this square; light it.
      SetViewable(now_pos);

      if (costly) {
        // we're scanning a row of costly squares.
        if (GetCost(now_pos) != 0) {
          CastLight(pos, radius - GetCost(now_pos), j + 1,
                    FractionType(dx * 2 - 1, dy * 2 - 1), r_slope, mult);
          new_start = r_slope;
          continue;
        } else {
          costly = false;
          start = new_start;
        }
      }

      else if (GetCost(now_pos) != 0) {
        // This is a costly square, start a child scan.
        costly = true;
        CastLight(pos, radius, j + 1, start, l_slope, mult);
        CastLight(pos, radius - GetCost(now_pos), j + 1, l_slope, r_slope,
                  mult);
        new_start = r_slope;
      }
    }
    if (costly) {
      break;
    }
  }
}

}  // namespace fov

#endif  // SRC_FOV_SHADOWCASTING_H
