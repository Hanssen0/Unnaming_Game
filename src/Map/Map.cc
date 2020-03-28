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
#include "Map.h"
#include <cassert>
#include <functional>
#include "./map_cmake.h"
size_t Map::kMapSize = 0;
MAP_EXPORT MapPoint Map::PickRandomPointIn(
    const std::function<size_t(size_t, size_t)>& ran,
    const std::list<Block>& valid_list) const {
  size_t total_valid = 0;
  for (size_t y = 0; y < Height(); ++y) {
    for (size_t x = 0; x < Width(); ++x) {
      for (auto i : valid_list) {
        if (i == BlockIn(MapPoint(x, y))) ++total_valid;
      }
    }
  }
  if (total_valid == 0) return MapPoint(0, 0);
  total_valid = ran(static_cast<size_t>(0), total_valid - 1);
  for (size_t y = 0; y < Height(); ++y) {
    for (size_t x = 0; x < Width(); ++x) {
      for (auto i : valid_list) {
        if (i == BlockIn(MapPoint(x, y))) {
          if (total_valid-- == 0) return MapPoint(x, y);
        }
      }
    }
  }
  return MapPoint(0, 0);
}
MAP_EXPORT Map_ref Map::Create(const Rect& size) {
  return Map_ref(new Map(size));
}
MAP_NO_EXPORT Map::Map(const Rect& size): size_(size) {
  assert(blocks_.max_size()/Width() >= Height());
  const auto map_size = Width()*Height();
  blocks_.resize(map_size);
  buildings_.resize(map_size);
  is_got_id_ = false;
}
MAP_EXPORT size_t Map::Id() {
  if (!is_got_id_) get_id();
  return id_;
}
MAP_EXPORT const Rect& Map::Size() const {return size_;}
MAP_EXPORT size_t Map::Width() const {return size_.w;}
MAP_EXPORT size_t Map::Height() const {return size_.h;}
MAP_EXPORT void Map::SetDestroy(const std::function<void()>& destroy) {
  destroy_ = destroy;
}
// Layer operators
MAP_NO_EXPORT Block* Map::BlockPtrIn(const MapPoint& pos) {
  return &blocks_[GetIndex(pos)];
}
MAP_NO_EXPORT Building* Map::BuildingPtrIn(const MapPoint& pos) {
  return &buildings_[GetIndex(pos)];
}
MAP_EXPORT const Block& Map::BlockIn(const MapPoint& pos) const {
  return blocks_[GetIndex(pos)];
}
MAP_EXPORT const Building& Map::BuildingIn(const MapPoint& pos) const {
  return buildings_[GetIndex(pos)];
}
MAP_EXPORT void Map::SetBlockIn(const MapPoint& pos, const Block& block) {
  *BlockPtrIn(pos) = block;
}
MAP_EXPORT void Map::SetBuildingIn(const MapPoint& pos,
                                   const Building& building) {
  *BuildingPtrIn(pos) = building;
}
MAP_EXPORT void Map::DestroyBlockIn(const MapPoint& pos) {
  const Block& destroy = BlockIn(pos).Destroy();
  if (destroy) SetBlockIn(pos, destroy);
}
MAP_EXPORT Map::~Map() {}
MAP_NO_EXPORT void Map::get_id() {
  if (!is_got_id_) {
    id_ = kMapSize++;
    is_got_id_ = true;
  }
}
MAP_EXPORT void Map::ForEachBlock(const std::function<void(Block*)>& applier) {
  for (size_t y = 0; y < Height(); ++y) {
    for (size_t x = 0; x < Width(); ++x) {
      applier(BlockPtrIn(MapPoint(x, y)));
    }
  }
}
MAP_EXPORT
void Map::ForEachBlockIn(const RectWithPos& region,
                         const std::function<void(Block*)>& applier) {
  const size_t end_y = region.left_top.y + region.size.h;
  const size_t end_x = region.left_top.x + region.size.w;
  for (size_t y = region.left_top.y; y < end_y; ++y) {
    for (size_t x = region.left_top.x; x < end_x; ++x) {
      applier(BlockPtrIn(MapPoint(x, y)));
    }
  }
}
MAP_EXPORT void Map::ForEachBuilding(
    const std::function<void(Building*)>& applier) {
  for (size_t y = 0; y < Height(); ++y) {
    for (size_t x = 0; x < Width(); ++x) {
      applier(BuildingPtrIn(MapPoint(x, y)));
    }
  }
}
MAP_EXPORT void Map::Link() {++links_num_;}
MAP_EXPORT void Map::Unlink() {
  if (--links_num_ == 0 && destroy_) destroy_();
}
MAP_EXPORT void Map::CopyFromIn(const Map& map, const MapPoint& pos) {
  SetBlockIn(pos, map.BlockIn(pos));
  SetBuildingIn(pos, map.BuildingIn(pos));
}
