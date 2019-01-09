//    Copyright (C) 2018  Handsome0hell
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.
//
//    Email: handsome0hell@gmail.com
#include "Map.h"
#include <list>
constexpr Map::Target Map::kNullTarget;
int32_t Map::kMapSize = 0;
Point Map::PickARandomPointInGroundOrPath(UniformIntRandom& ran) const {
  for (int32_t i = 0; i < width_; ++i) {
    if (ran.rand(i + 1, width_) == width_) {
      for (int32_t j = 0; j < height_; ++j) {
        if (ran.rand(j + 1, height_) == height_) {
          if (block(CreatePoint(i, j)) == kBlockPath ||
              block(CreatePoint(i, j)) == kBlockGround) {
            return CreatePoint(i, j);
          }
        }
      }
    }
  }
  return CreatePoint(0, 0);
}
