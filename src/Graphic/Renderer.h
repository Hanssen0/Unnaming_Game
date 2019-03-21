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
#include "../Map/Space.h"
#include "../Object/Creature.h"
#include <memory>
#include <vector>
class Renderer;
typedef std::shared_ptr< Renderer > Renderer_ref;
class Renderer {
 public:
  void UpdateBlockTypeSize(size_t size);
  void set_exterior_of_block(const char exterior, const Map::BlockType& type);
  void RenderCreaturesView(const Creature&) const;
  void RenderGameMap(const Map&) const;
  void RenderMemory(const Space::MemoryOfMap&) const;
  static Renderer_ref Create();
 private:
  Renderer();
  Renderer& operator=(const Renderer&) = delete;
  std::vector< char > exterior_of_block_;
};
#endif  // UNNAMING_GAME_SRC_GRAPHIC_RENDERER_H_
