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
#ifndef UNNAMING_GAME_SRC_MAP_GAMEMAP_H_
#define UNNAMING_GAME_SRC_MAP_GAMEMAP_H_
#include "../Base.h"
#include <cstdint>
#include <list>
#include <algorithm>
#include <queue>
#include <map>
struct Point {
  uint32_t x, y;
};
inline Point TempPoint(uint32_t x, uint32_t y) {
  Point tmp = {x, y};
  return tmp;
}
inline bool operator<(const Point & a, const Point & b) {
  if (a.x == b.x) {
    return a.y < b.y;
  } else {
    return a.x < b.x;
  }
}
inline bool operator==(const Point & a, const Point & b) {
  return a.x == b.x && a.y == b.y;
}
struct Rect {
  uint32_t w, h;
};
struct RectWithPos {
  Point left_top;
  uint32_t w, h;
};
const uint32_t kMapWidth = 32;
const uint32_t kMapHeight = 32;
const uint32_t kMinRoomWidth = 3;
const uint32_t kMinRoomHeight = 3;
const uint32_t kMaxRoomWidth = 8;
const uint32_t kMaxRoomHeight = 8;
const uint32_t kNumeratorOfPossibilityOfPortal = 1;
const uint32_t kDenominatorOfPossibilityOfPortal = 30;
enum BlockType {
  kBlockEmpty,
  kBlockWall,
  kBlockGround,
  kBlockPath,
  kBlockMax
};
enum ItemType {
};
enum BuildingType {
  kBuildingEmpty,
  kBuildingPortal
};
class GameMap {
 public:
  struct TargetInMap {
    GameMap * target_map;
    Point target_pos;
  };
  virtual inline void set_data_block(const Point & pos, const BlockType type) {
    data_[pos.x][pos.y].block = type;
  }
  virtual inline BlockType data_block(const Point & pos) const {return data_[pos.x][pos.y].block;}
  virtual inline void set_data_building(const Point & pos, const BuildingType type) {
    data_[pos.x][pos.y].building = type;
  }
  virtual inline BuildingType data_building(const Point & pos) const {
    return data_[pos.x][pos.y].building;
  }
  virtual inline void set_portal_target(const Point & pos, const TargetInMap & target) {
    if (target.target_map == nullptr) return;
    if (data_building(pos)== kBuildingPortal) {
      portal_target_[pos] = target;
    }
  }
  virtual inline TargetInMap * portal_target(const Point & pos) const {
    auto ret = portal_target_.find(pos);
    if (ret == portal_target_.end()) {
      return nullptr;
    } else {
      return const_cast< TargetInMap * >(&(ret -> second));
    }
  }
  Point PickARandomPointInGroundOrPath(RandomGenerater *);

 private:
  struct BlockData {
    BlockType block;
    BuildingType building;
  };
  BlockData data_[kMapWidth][kMapHeight];
  std::map< Point, TargetInMap > portal_target_;
};
class GameMapBuilder {
 public:
  GameMapBuilder(RandomGenerater * ran) : random_gen_(ran) {
    target_map_ = nullptr;
  }
  // Delete everything
  void CleanMap();
  // Make rooms
  void BuildRoomsAndPath();
  void BuildBuildings();
  void set_random_gen(RandomGenerater * r) {random_gen_ = r;}
  void set_target_map(GameMap * target) {target_map_ = target;}

 private:
  // Init to speed up empty test
  void InitForEmptyTest();
  // Update array to speed up empty test
  void UpdateCheckedBuildAble(const Point & pos_to_update);
  // Build path by A*
  void BuildPath(const Point & from, const Point & to);
  bool SelectRoomPosition(RectWithPos *);
  // Build one room
  bool BuildRoom(Point * room_pos);
  bool IsRectEmpty(const RectWithPos & rect_for_check);
  inline Rect RandomRoomRect();
  inline const Rect & max(const Rect &, const Rect &);
  // To speed up empty test
  Rect checked_build_able_[kMapWidth][kMapHeight];
  RandomGenerater * random_gen_;
  GameMap * target_map_;
};
class PathFinder {
 public:
  std::list< Point > FindShortestPath(const Point & from, const Point & to);
  inline void set_value(BlockType type, uint32_t value) {
    value_[type] = value;
  }
  void set_target_map(GameMap * target) {target_map_ = target;}

 private:
  struct AstarStat {
    Point self;
    PathFinder * original_finder;
  };
  void UpdateNearby(const Point & now);
  bool TryAPoint(const BlockType type, uint32_t walked_dis, const Point & now);
  void PushPointToAstarList(const Point &);
  uint32_t value_[kBlockMax];
  // A star data
  bool walked_[kMapWidth][kMapHeight];
  uint32_t walked_dis_[kMapWidth][kMapHeight];
  bool is_first_check[kMapWidth][kMapHeight];
  Point father[kMapWidth][kMapHeight];
  std::list< Point > searching_list;
  GameMap * target_map_;
};
inline Rect GameMapBuilder::RandomRoomRect() {
  Rect ret;
  // Need some space to prevent room adhesion
  ret.w = random_gen_ -> RandomIn(kMinRoomWidth + 2, kMaxRoomWidth + 2);
  ret.h = random_gen_ -> RandomIn(kMinRoomHeight + 2, kMaxRoomHeight + 2);
  return ret;
}
inline const Rect & GameMapBuilder::max(const Rect & a, const Rect & b) {
  if (a.w < 0 || a.h < 0) return b;
  if (b.w < 0 || b.h < 0) return a;
  uint64_t a_area = a.w, b_area = b.w;
  a_area *= a.h, b_area *= b.h;
  if (a_area > b_area) {
    return a;
  } else {
    return b;
  }
}
#endif  // UNNAMING_GAME_SRC_MAP_GAMEMAP_H_
