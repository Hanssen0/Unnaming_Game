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
#include "../Interface/Random.h"
#include <cstdint>
#include <vector>
#include <list>
#include <map>
struct Point {
  int32_t x, y;
};
struct Rect {
  int32_t w, h;
};
struct RectWithPos {
  Point left_top;
  int32_t w, h;
};
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
inline const Point CreatePoint(const int32_t& x, const int32_t& y) {
  const Point tmp = {x, y};
  return tmp;
}
inline const Rect CreateRect(const int32_t& w, const int32_t& h) {
  const Rect tmp = {w, h};
  return tmp;
}
class Map final {
 public:
  enum BlockType {
    kBlockEmpty,
    kBlockWall,
    kBlockGround,
    kBlockPath,
    kBlockMax
  };
  struct Target {
    Map* map;
    Point pos;
  };
  inline Map(const int32_t& w, const int32_t& h)
      : width_(w), height_(h) {
    block_.resize(w, std::vector< BlockType >(h));
    is_got_id_ = false;
  }
  inline void get_id();
  inline const int32_t map_id();
  inline const BlockType& block(const Point& pos) const;
  inline const int32_t width() const {return width_;}
  inline const int32_t height() const {return height_;}
  inline void set_block(const Point& pos,
                        const BlockType& block);
  inline const Target& portal_target(const Point& pos) const;
  inline void set_portal_target(const Point& pos,
                                const Target& target);
  inline void FillWith(const BlockType& block);
  const Point PickARandomPointInGroundOrPath(UniformIntRandom&) const;

 private:
  static int32_t kMapSize;
  const int32_t width_;
  const int32_t height_;
  constexpr static Target kNullTarget = {nullptr, {0, 0}};
  bool is_got_id_;
  int32_t map_id_;
  std::vector< std::vector< BlockType > > block_;
  std::map< Point, Target > portal_target_;
};
inline void Map::get_id() {
  if (!is_got_id_) {
    map_id_ = kMapSize++;
    is_got_id_ = true;
  }
}
inline const int32_t Map::map_id() {
  if (!is_got_id_) {
    get_id();
  }
  return map_id_;
}
inline const Map::BlockType& Map::block(const Point& pos) const {
  return block_[pos.x][pos.y];
}
inline void Map::set_block(const Point& pos,
                           const BlockType& block) {
  block_[pos.x][pos.y] = block;
}
inline const Map::Target& Map::portal_target(const Point& pos)
    const {
  auto ret = portal_target_.find(pos);
  if (ret == portal_target_.end()) {
    return kNullTarget;
  } else {
    return ret -> second;
  }
}
inline void Map::set_portal_target(const Point& pos,
                                       const Target& target) {
  auto finder = portal_target_.find(pos);
  if (target.map == nullptr) {
    if (finder != portal_target_.end()) {
      portal_target_.erase(finder);
    }
  } else {
    portal_target_[pos] = target;
  }
}
inline void Map::FillWith(const BlockType& block) {
  for (int32_t i = 0; i < width_; ++i) {
    for (int32_t j = 0; j < height_; ++j) {
      block_[i][j] = block;
    }
  }
}
#endif  // UNNAMING_GAME_SRC_MAP_MAP_H_
