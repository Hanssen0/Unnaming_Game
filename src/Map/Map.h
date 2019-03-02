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
#ifndef UNNAMING_GAME_SRC_MAP_MAP_H_
#define UNNAMING_GAME_SRC_MAP_MAP_H_
#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <vector>
struct Point {
  int32_t x, y;
};
struct Rect {
  int32_t w, h;
};
struct RectWithPos {
  Point left_top;
  Rect size;
};
inline bool operator<(const Point& a, const Point& b) {
  if (a.x == b.x) {
    return a.y < b.y;
  } else {
    return a.x < b.x;
  }
}
inline bool operator==(const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
}
class Map;
typedef std::shared_ptr< Map > Map_ref;
class Map final {
 public:
  enum BlockType {
    kBlockEmpty,
    kBlockWall,
    kBlockGround,
    kBlockPath,
    kBlockMax
  };
  enum BuildingType {
    kBuildingEmpty,
    kBuildingPortal
  };
  struct Target {
    Map* map;
    Point pos;
  };
  static Map_ref Create(int32_t w, int32_t h);
  int32_t Id();
  int32_t Width() const;
  int32_t Height() const;
  const BlockType& Block(const Point& pos) const;
  void SetBlock(const Point& pos, const BlockType& block);
  const BuildingType& Building(const Point& pos) const;
  void SetBuilding(const Point& pos, const BuildingType& building);
  const Target& PortalTarget(const Point& pos) const;
  void SetPortalTarget(const Point& pos, const Target& target);
  void ForEachBuilding(const std::function< void(BuildingType*) >& applier);
  void ForEachBlock(const std::function< void(BlockType*) >& applier);
  Point PickARandomPointInGroundOrPath(
      const std::function< int32_t(int32_t, int32_t) >& ran) const;
 private:
  Map(int32_t w, int32_t h);
  void get_id();
  static int32_t kMapSize;
  const int32_t width_;
  const int32_t height_;
  constexpr static Target kNullTarget = {nullptr, {0, 0}};
  bool is_got_id_;
  int32_t id_;
  std::vector< std::vector< BlockType > > block_;
  std::vector< std::vector< BuildingType > > building_;
  std::map< Point, Target > portal_target_;
};
#endif  // UNNAMING_GAME_SRC_MAP_MAP_H_
