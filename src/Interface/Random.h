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
#ifndef UNNAMING_GAME_SRC_INTERFACE_RANDOM_H_
#define UNNAMING_GAME_SRC_INTERFACE_RANDOM_H_
#include <cstdint>
class UniformIntRandom {
 public:
  inline virtual ~UniformIntRandom() = default;
  virtual const int32_t rand(const int32_t& from, const int32_t& to) = 0;
  virtual void set_seed(const int32_t& seed) = 0;
};
#endif  // UNNAMING_GAME_SRC_INTERFACE_RANDOM_H_
