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
#include <functional>
constexpr Map::Target Map::kNullTarget;
int32_t Map::kMapSize = 0;
Point Map::PickARandomPointInGroundOrPath(
    const std::function< int32_t(int32_t, int32_t) >& ran) const {
  for (int32_t i = 0; i < width_; ++i) {
    if (ran(i + 1, width_) == width_) {
      for (int32_t j = 0; j < height_; ++j) {
        if (ran(j + 1, height_) == height_) {
          if (Block({i, j}) == kBlockPath || Block({i, j}) == kBlockGround) {
            return Point({i, j});
          }
        }
      }
    }
  }
  return Point({0, 0});
}
Map_ref Map::Create(int32_t w, int32_t h) {
  return Map_ref(new Map(w, h));
}
Map::Map(int32_t w, int32_t h) : width_(w), height_(h) {
  block_.resize(w, std::vector< BlockType >(h));
  is_got_id_ = false;
}
int32_t Map::Id() {
  if (!is_got_id_) get_id();
  return id_;
}
int32_t Map::Width() const {return width_;}
int32_t Map::Height() const {return height_;}
const Map::BlockType& Map::Block(const Point& pos) const {
  return block_[pos.x][pos.y];
}
void Map::SetBlock(const Point& pos, const BlockType& block) {
  block_[pos.x][pos.y] = block;
}
const Map::BuildingType& Map::Building(const Point& pos) const {
  return building_[pos.x][pos.y];
}
void Map::SetBuilding(const Point& pos,
                         const BuildingType& building) {
  if (building_[pos.x][pos.y] == building) return;
  if (building_[pos.x][pos.y] == kBuildingPortal) {
    SetPortalTarget(pos, {nullptr, {0, 0}});
  }
  building_[pos.x][pos.y] = building;
}
const Map::Target& Map::PortalTarget(const Point& pos) const {
  auto ret = portal_target_.find(pos);
  if (ret == portal_target_.end()) {
    return kNullTarget;
  } else {
    return ret -> second;
  }
}
void Map::SetPortalTarget(const Point& pos, const Target& target) {
  auto finder = portal_target_.find(pos);
  if (target.map == nullptr) {
    if (finder != portal_target_.end()) {
      portal_target_.erase(finder);
    }
  } else {
    portal_target_[pos] = target;
  }
}
void Map::get_id() {
  if (!is_got_id_) {
    id_ = kMapSize++;
    is_got_id_ = true;
  }
}
void Map::ForEachBuilding(const std::function< void(BuildingType*) >& applier) {
  for (size_t y = 0; y < height_; ++y) {
    for (size_t x = 0; x < width_; ++x) {
      applier(&(building_[x][y]));
    }
  }
}
void Map::ForEachBlock(const std::function< void(BlockType*) >& applier) {
  for (size_t y = 0; y < height_; ++y) {
    for (size_t x = 0; x < width_; ++x) {
      applier(&(block_[x][y]));
    }
  }
}
