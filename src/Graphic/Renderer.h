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
#ifndef UNNAMING_GAME_SRC_GRAPHIC_RENDERER_H_
#define UNNAMING_GAME_SRC_GRAPHIC_RENDERER_H_
#include "../Map/Map.h"
#include "../Map/World.h"
#include "../Interface/Object.h"
#include <memory>
class Renderer;
typedef std::shared_ptr< Renderer > Renderer_ref;
class Renderer {
 public:
  void set_exterior_of_block(const char exterior, const Map::BlockType& type);
  void RenderLivingThingsView(const Object&) const;
  void RenderGameMap(const Map&) const;
  void RenderMemory(const World::MemoryOfMap&) const;
  static Renderer_ref CreateRenderer();
 private:
  Renderer();
  Renderer& operator=(const Renderer&) = delete;
  char exterior_of_block_[Map::kBlockMax];
};
#endif  // UNNAMING_GAME_SRC_GRAPHIC_RENDERER_H_
