#include "shadowcasting.h"
#include <cstring>

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
      int x = GetCost(now_pos);
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
