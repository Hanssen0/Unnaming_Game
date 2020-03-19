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
#ifndef UNNAMING_GAME_SRC_MAP_SPACE_H_
#define UNNAMING_GAME_SRC_MAP_SPACE_H_
#include <map>
#include <cassert>
#include <functional>
#include <list>
#include <vector>
#include <utility>
#include "./Map.h"
#include "../Logic/MapBuilder.h"
class Space {
 public:
  struct MemoryOfMap {
    Point left_top;
    Point right_bottom;
    std::vector< std::vector< bool > > is_seen;
    Map_ref detail;
  };
  inline Space(const std::function< int32_t(int32_t, int32_t) >& ran,
               MapBuilder* builder, const Rect& nms) :
               builder_(builder), random_gen_(ran), next_map_size_(nms) {}
  inline void set_next_map_size(const Rect& si) {next_map_size_ = si;}
  inline Map* NewMap();
  inline const Map::Target GetTarget(Map* map, const Point& pos);
  inline void Arrive(Map* map);
  inline void Left(Map* map);
  inline MemoryOfMap& GetMemory(int32_t obj_id, Map* map);

 private:
  struct MapInformation {
    Map_ref map;
    int32_t connections_num;
    std::map< int32_t, MemoryOfMap > memories_;
  };
  std::map< int32_t, MapInformation > id_to_map_;
  MapBuilder* const builder_;
  const std::function< int32_t(int32_t, int32_t) > random_gen_;
  Rect next_map_size_;
};
inline Map* Space::NewMap() {
  MapInformation tmp = {Map::Create(next_map_size_.w, next_map_size_.h), 0,
                        std::map< int32_t, MemoryOfMap>()};
  // TODO(handsome0hell): Read block type from file
  tmp.map->ForEachBlock([](Map::BlockType* block){*block = 1;});
  builder_->SetWallBlock(1);
  builder_->SetPathBlock(2);
  builder_->SetGroundBlock(3);
  builder_->set_target_map(tmp.map.get());
  builder_->BuildRoomsAndPath();
  auto inserter = id_to_map_.insert(std::make_pair(tmp.map->Id(), tmp));
  return inserter.first->second.map.get();
}
inline const Map::Target Space::GetTarget(Map* map, const Point& pos) {
  Map::Target ret = map->PortalTarget(pos);
  if (ret.map == nullptr) {
    ret.map = NewMap();
    // TODO(handsome0hell): Read block type from file
    std::list< Map::BlockType > valid;
    valid.push_back(2);
    valid.push_back(3);
    ret.pos = ret.map->PickARandomPointInGroundOrPath(random_gen_, valid);
    map->SetPortalTarget(pos, ret);
  }
  return ret;
}
inline void Space::Arrive(Map* map) {
  auto finder = id_to_map_.find(map->Id());
  assert((finder != id_to_map_.end()));
  ++(finder->second.connections_num);
}
inline void Space::Left(Map* map) {
  auto finder = id_to_map_.find(map->Id());
  assert(finder != id_to_map_.end());
  if (--(finder->second.connections_num) <= 0) {
    id_to_map_.erase(finder);
  }
}
inline Space::MemoryOfMap& Space::GetMemory(int32_t obj_id, Map* map) {
  auto info_finder = id_to_map_.find(map->Id());
  assert(info_finder != id_to_map_.end());
  // For shorter code
  MapInformation* const map_finder = &(info_finder->second);
  auto obj_finder = (map_finder->memories_).find(obj_id);
  if (obj_finder == (map_finder->memories_).end()) {
    const MemoryOfMap tmp = {{map_finder->map->Width(),
                              map_finder->map->Height()}, {0, 0},
                             std::vector< std::vector< bool > >(
                                 map_finder->map->Width(),
                                 std::vector< bool >(
                                     map_finder->map->Height(), false)),
                                 Map::Create(map_finder->map->Width(),
                                             map_finder->map->Height())};
    obj_finder = (map_finder->memories_).insert(
                     std::make_pair(map_finder->map->Id(), tmp)).first;
  }
  return obj_finder->second;
}
#endif  // UNNAMING_GAME_SRC_MAP_SPACE_H_
