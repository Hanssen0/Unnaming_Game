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
#include "../CPP.h"
#include "../ConstValue.h"
#include "cstdint"
struct Point {
  uint32_t x, y;
};
inline Point TempPoint(uint32_t x, uint32_t y) {
  Point tmp = {x, y};
  return tmp;
}
struct Rect {
  uint32_t w, h;
};
struct RectWithPos {
  Point left_top;
  uint32_t w, h;
};
class GameMap {
 public:
  inline BlockType data(const Point & pos) const {return data_[pos.x][pos.y];}
  inline void set_data(const Point & pos, const BlockType type) {
    data_[pos.x][pos.y] = type;
  }
  friend class GameMapBuilder;
  friend class PathFinder;
 private:
  BlockType data_[kMapWidth][kMapHeight];
};
class GameMapBuilder {
 public:
  GameMapBuilder() {random_gen_ = nullptr;}
  // Delete everything
  void CleanMap();
  // Make rooms
  void BuildRoomsAndPath();
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
