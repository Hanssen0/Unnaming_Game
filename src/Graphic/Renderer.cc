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
#include "Renderer.h"
#include <cstdint>
#include <iostream>
#include "./renderer_cmake.h"
#include "../Map/Building/BaseBuilding.h"
#include "../Map/Map.h"
#include "../Object/Creature.h"
template<typename T> void Expand(std::vector<T>* const vec, size_t size) {
  if (vec->size() < size) vec->resize(size);
}
RENDERER_EXPORT Renderer::~Renderer() {}
RENDERER_EXPORT
void Renderer::set_exterior_of_building(const char exterior,
                                        const Building& type) {
  Expand(&exterior_of_building_, type.Size());
  exterior_of_building_[type.Index()] = exterior;
}
RENDERER_EXPORT void Renderer::RenderPosition(const Map& map,
                                              const MapPoint& pos) const {
  auto building = exterior_of_building_[map.BuildingIn(pos).Index()];
  if (building != 0) {
    std::cout << building;
  } else {
    std::cout << exterior_of_building_[map.GroundIn(pos).Index()];
  }
}
RENDERER_EXPORT void Renderer::RenderCreaturesView(const Creature& obj) const {
  for (size_t j = 0; j < ((obj.view_dis() << 1) | 1); ++j) {
    for (size_t i = 0; i < ((obj.view_dis() << 1) | 1); ++i) {
      MapPoint tmp = obj.position() + MapPoint(i, j);
      if (tmp < obj.view_dis()) {
        std::cout << ' ';
        continue;
      }
      tmp -= obj.view_dis();
      if (tmp == obj.position()) {
        std::cout << "@";
      } else if (obj.is_viewable(tmp)) {
        RenderPosition(*obj.map(), MapPoint(tmp));
      } else {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
}
RENDERER_EXPORT void Renderer::RenderGameMap(const Map& map) const {
  for (size_t j = 0; j < map.Height(); ++j) {
    for (size_t i = 0; i < map.Width(); ++i) {
      RenderPosition(map, {i, j});
    }
    std::cout << "\n";
  }
}
RENDERER_EXPORT void Renderer::RenderMemory(
                         const Creature::Memory& mem) const {
  for (auto j = mem.left_top.y; j <= mem.right_bottom.y; ++j) {
    for (auto i = mem.left_top.x; i <= mem.right_bottom.x; ++i) {
      if (mem.is_seen[i][j]) {
        RenderPosition(*mem.detail, {i, j});
      } else {
        std::cout << ' ';
      }
    }
    std::cout << "\n";
  }
}
RENDERER_EXPORT Renderer_ref Renderer::Create() {
  return Renderer_ref(new Renderer);
}
RENDERER_NO_EXPORT Renderer::Renderer() {}
