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
#include <random>
constexpr Map::Target Map::kNullTarget;
const Point Map::PickARandomPointInGroundOrPath(std::default_random_engine& ran) const {
  static std::uniform_int_distribution< unsigned int > rand_dis;
  typedef std::uniform_int_distribution< unsigned int >::param_type party;
  for (int32_t i = 0; i < width_; ++i) {
    if (rand_dis(ran, party(i + 1, width_)) == width_) {
      for (int32_t j = 0; j < height_; ++j) {
        if (rand_dis(ran, party(j + 1, height_)) == height_) {
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
