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
#ifndef UNNAMING_GAME_SRC_INTERFACE_INPUT_H_
#define UNNAMING_GAME_SRC_INTERFACE_INPUT_H_
#include "Object.h"
#include "../Map/Map.h"
#include <cstdint>
class Input {
 public:
  class Command {
   public:
    virtual ~Command() = default;
    virtual void Execute(Object& obj) = 0;
    virtual void Record(const Point&) {}
    virtual void Record(const Map::BlockType&) {}
  };
  virtual ~Input() = default;
  virtual Command& HandleInput() = 0;
};
#endif  // UNNAMING_GAME_SRC_INTERFACE_INPUT_H_
