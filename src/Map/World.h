#ifndef UNNAMING_GAME_SRC_MAP_WORLD_H_
#define UNNAMING_GAME_SRC_MAP_WORLD_H_
#include "Map.h"
#include "../Logic/MapBuilder.h"
#include "../Interface/Random.h"
#include <map>
#include <cassert>
#include <iostream>
class World {
 public:
  struct MemoryOfMap {
    Point left_top;
    Point right_bottom; 
    std::vector< std::vector< bool > > is_seen;
    Map detail;
  };
  inline World(UniformIntRandom* const ran, MapBuilder* builder,
               const Rect& nms) :
               builder_(builder),
               random_gen_(ran),
               next_map_size_(nms) {
  }
  inline void set_next_map_size(const Rect& si) {next_map_size_ = si;}
  inline Map* const NewMap();
  inline const Map::Target GetTarget(Map& map, const Point& pos);
  inline void Arrive(Map& map);
  inline void Left(Map& map);
  inline MemoryOfMap& GetMemory(int32_t obj_id, Map& map);

 private:
  struct MapInformation {
    Map map;
    int32_t connections_num;
    std::map< int32_t, MemoryOfMap > memories_;
  };
  std::map< int32_t, MapInformation > id_to_map_;
  MapBuilder* const builder_;
  UniformIntRandom* const random_gen_;
  Rect next_map_size_;
};
inline Map* const World::NewMap() {
  MapInformation tmp = {Map(next_map_size_.w, next_map_size_.h), 0};
  tmp.map.FillWithBlock(Map::kBlockWall);
  builder_ -> set_target_map(&tmp.map);
  builder_ -> BuildRoomsAndPath();
  auto inserter = id_to_map_.insert(std::make_pair(tmp.map.id(), tmp));
  return &(inserter.first -> second.map);
}
inline const Map::Target World::GetTarget(Map& map, const Point& pos) {
  Map::Target ret = map.portal_target(pos);
  if (ret.map == nullptr) {
    ret.map = NewMap();
    ret.pos = ret.map -> PickARandomPointInGroundOrPath(
                             *random_gen_);
    map.set_portal_target(pos, ret);
  }
  return ret;
}
inline void World::Arrive(Map& map) {
  auto finder = id_to_map_.find(map.id());
  assert((finder != id_to_map_.end()));
  ++(finder -> second.connections_num);
}
inline void World::Left(Map& map) {
  auto finder = id_to_map_.find(map.id());
  assert(finder != id_to_map_.end());
  if(--(finder -> second.connections_num) <= 0) {
    id_to_map_.erase(finder);
  }
}
inline World::MemoryOfMap& World::GetMemory(int32_t obj_id, Map& map) {
  auto info_finder = id_to_map_.find(map.id());
  assert(info_finder != id_to_map_.end());
  //For shorter code
  MapInformation* const map_finder= &(info_finder -> second);
  auto obj_finder = (map_finder -> memories_).find(obj_id);
  if (obj_finder == (map_finder -> memories_).end()) {
    const MemoryOfMap tmp = {{(map_finder -> map).width(),
                              (map_finder -> map).height()}, {0, 0},
                             std::vector< std::vector< bool > >(
                                 (map_finder -> map).width(),
                                 std::vector< bool >(
                                     (map_finder -> map).height(), false)),
                                 Map((map_finder -> map).width(),
                                     (map_finder -> map).height())};
    obj_finder = (map_finder -> memories_).insert(
                     std::make_pair((map_finder -> map).id(), tmp)).first;
  }
  return obj_finder -> second;
}
#endif  // UNNAMING_GAME_SRC_MAP_WORLD_H_
