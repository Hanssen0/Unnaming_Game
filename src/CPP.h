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
#ifndef UNNAMING_GAME_SRC_CPP_H_
#define UNNAMING_GAME_SRC_CPP_H_
#include <iostream>
#include <utility>
#include <cstdlib>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <queue>
#include <stack>
#include <climits>
class RandomGenerater {
 public:
  inline void set_seed_of_random(uint32_t a) {seed_of_random_ = a % UINT_MAX;}
  inline uint32_t RandomIn(uint32_t start, uint32_t end) {
    if (start > end) std::swap(start, end);
    if (end - start > RAND_MAX) return UINT32_MAX;
    return (rand_r(&seed_of_random_) % (end - start + 1)) + start;
  }
 private:
  unsigned int seed_of_random_;
};
#endif  // UNNAMING_GAME_SRC_CPP_H_
