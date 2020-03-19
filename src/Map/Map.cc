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
#include <map_export.h>  // Generated by Cmake
#include <cassert>
#include <functional>
#include "Map.h"
int32_t Map::kMapSize = 0;
MAP_EXPORT Point Map::PickRandomPointIn(
    const std::function< int32_t(int32_t, int32_t) >& ran,
    const std::list<BlockPtr>& valid_list) const {
  int32_t total_valid = 0;
  for (int32_t y = 0; y < height_; ++y) {
    for (int32_t x = 0; x < width_; ++x) {
      for (auto i : valid_list) {
        if (i == BlockIn({x, y})) ++total_valid;
      }
    }
  }
  total_valid = ran(0, total_valid - 1);
  for (int32_t y = 0; y < height_; ++y) {
    for (int32_t x = 0; x < width_; ++x) {
      for (auto i : valid_list) {
        if (i == BlockIn({x, y})) {
          if (total_valid-- == 0) return Point({x, y});
        }
      }
    }
  }
  return Point({0, 0});
}
MAP_EXPORT Map_ref Map::Create(int32_t w, int32_t h) {
  return Map_ref(new Map(w, h));
}
MAP_NO_EXPORT Map::Map(int32_t w, int32_t h) : width_(w), height_(h) {
  // TODO(handsome0hell): Use size_t instead of int32_t for map width and
  // height.
  assert(blocks_.max_size()/w >= static_cast<size_t>(h));
  const auto map_size = w*h;
  blocks_.resize(map_size);
  is_got_id_ = false;
}
MAP_EXPORT int32_t Map::Id() {
  if (!is_got_id_) get_id();
  return id_;
}
MAP_EXPORT int32_t Map::Width() const {return width_;}
MAP_EXPORT int32_t Map::Height() const {return height_;}
// Layer operators
MAP_NO_EXPORT BlockPtr* Map::BlockPtrIn(const Point& pos) {
  return &blocks_[GetIndex(pos)];
}
MAP_NO_EXPORT BuildingPtr* Map::BuildingPtrIn(const Point& pos) {
  return &buildings_[GetIndex(pos)];
}
MAP_EXPORT const BlockPtr& Map::BlockIn(const Point& pos) const {
  return blocks_[GetIndex(pos)];
}
MAP_EXPORT const BuildingPtr& Map::BuildingIn(const Point& pos) const {
  return buildings_[GetIndex(pos)];
}
MAP_EXPORT void Map::SetBlockIn(const Point& pos, const BlockPtr& block) {
  *BlockPtrIn(pos) = block;
}
MAP_EXPORT void Map::SetBuildingIn(const Point& pos,
                                   const BuildingPtr& building) {
  *BuildingPtrIn(pos) = building;
}
MAP_EXPORT Map::~Map() {}
MAP_NO_EXPORT void Map::get_id() {
  if (!is_got_id_) {
    id_ = kMapSize++;
    is_got_id_ = true;
  }
}
MAP_EXPORT void Map::ForEachBlock(
    const std::function< void(BlockPtr*) >& applier) {
  for (int32_t y = 0; y < height_; ++y) {
    for (int32_t x = 0; x < width_; ++x) {
      applier(BlockPtrIn({x, y}));
    }
  }
}
MAP_EXPORT
void Map::ForEachBlockIn(const RectWithPos& region,
                         const std::function< void(BlockPtr*) >& applier) {
  const int32_t end_y = region.left_top.y + region.size.h;
  const int32_t end_x = region.left_top.x + region.size.w;
  for (int32_t y = region.left_top.y; y < end_y; ++y) {
    for (int32_t x = region.left_top.x; x < end_x; ++x) {
      applier(BlockPtrIn({x, y}));
    }
  }
}
