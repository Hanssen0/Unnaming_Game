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
#ifndef UNNAMING_GAME_SRC_MAP_MAP_H_
#define UNNAMING_GAME_SRC_MAP_MAP_H_
#include <cassert>
#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <vector>
#include "./Block.h"
#include "./Building/Building.h"
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
  struct MemoryOfMap {
    Point left_top;
    Point right_bottom;
    std::vector< std::vector< bool > > is_seen;
    Map_ref detail;
  };
  struct Rules {
    BlockPtr empty_block;
  };
  static Map_ref Create(const Rect&);
  // Basic attributes
  int32_t Id();
  const Rect& Size() const;
  int32_t Width() const;
  int32_t Height() const;
  void SetDestory(const std::function<void()>&);
  void SetEmptyBlock(const BlockPtr&);
  // Layer
  const BlockPtr& BlockIn(const Point&) const;
  const Building& BuildingIn(const Point&) const;
  void SetBlockIn(const Point&, const BlockPtr&);
  void SetBuildingIn(const Point&, const Building&);
  void DestoryBlockIn(const Point&);
  ~Map();
  void ForEachBlock(const std::function< void(BlockPtr*) >& applier);
  void ForEachBlockIn(const RectWithPos& region,
                      const std::function< void(BlockPtr*) >& applier);
  void ForEachBuilding(const std::function< void(const Building**) >& applier);
  void Link();
  void Unlink();
  Point PickRandomPointIn(const std::function< int32_t(int32_t, int32_t) >& ran,
                          const std::list<BlockPtr>& valid_list) const;
  void CopyFromIn(const Map&, const Point&);
  MemoryOfMap& GetMemory(int32_t);
  inline bool has(const Point& pos) const {
    return 0 <= pos.x && pos.x < Width() && 0 <= pos.y && pos.y < Height();
  }

 private:
  Map(const Rect&);
  void Init();
  void get_id();
  size_t GetIndex(const Point& pos) const {
    assert(pos.y < Height());
    assert(pos.x < Width());
    return pos.y*Width() + pos.x;
  }
  BlockPtr* BlockPtrIn(const Point& pos);
  const Building** BuildingPtrIn(const Point& pos);
  static int32_t kMapSize;
  const Rect size_;
  bool is_got_id_;
  int32_t id_;
  int32_t links_num_;
  BlockPtr empty_block_;
  std::function<void()> destory_;
  std::map<int32_t, MemoryOfMap> memories_;
  std::vector<BlockPtr> blocks_;
  std::vector<const Building*> buildings_;
};
#endif  // UNNAMING_GAME_SRC_MAP_MAP_H_
