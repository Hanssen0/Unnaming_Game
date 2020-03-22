// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#ifndef UNNAMING_GAME_SRC_GRAPHIC_RENDERER_H_
#define UNNAMING_GAME_SRC_GRAPHIC_RENDERER_H_
#include <memory>
#include <vector>
#include "../Map/Block/Block.h"
#include "../Map/Building/Building.h"
#include "../Map/Map.h"
#include "../Object/Creature.h"
class Renderer;
typedef std::shared_ptr< Renderer > Renderer_ref;
class Renderer {
 public:
  void set_exterior_of_block(const char, const BlockPtr&);
  void set_exterior_of_building(const char, const Building&);
  ~Renderer();
  void RenderCreaturesView(const Creature&) const;
  void RenderGameMap(const Map&) const;
  void RenderMemory(const Map::MemoryOfMap&) const;
  static Renderer_ref Create();
 private:
  Renderer();
  Renderer& operator=(const Renderer&) = delete;
  void RenderPosition(const Map&, const MapPoint&) const;
  std::vector< char > exterior_of_block_;
  std::vector< char > exterior_of_building_;
};
#endif  // UNNAMING_GAME_SRC_GRAPHIC_RENDERER_H_
