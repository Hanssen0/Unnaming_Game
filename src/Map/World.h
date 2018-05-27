#ifndef UNNAMING_GAME_SRC_MAP_WORLD_H_
#define UNNAMING_GAME_SRC_MAP_WORLD_H_
#include "Map.h"
#include "../Interface/Random.h"
#include <map>
#include <cassert>
#include <iostream>
class World {
 public:
  inline World(UniformIntRandom& ran, MapBuilder& builder) :
             builder_(&builder), random_gen_(&ran){
  }
  inline Map& NewMap();
  inline const Map::Target GetTarget(Map& map, const Point& pos);
  inline void Arrive(Map& map);
  inline void Left(Map& map);

 private:
  struct MapInformation {
    Map map;
    int32_t connections_num;
  };
  std::map< int32_t, MapInformation > id_to_map_;
  MapBuilder* const builder_;
  UniformIntRandom* const random_gen_;
};
inline Map& World::NewMap() {
  MapInformation tmp = {Map(32, 32), 0};
  tmp.map.get_id();
  tmp.map.FillWithBlock(Map::kBlockWall);
  builder_ -> set_target_map(tmp.map);
  builder_ -> BuildRoomsAndPath();
  auto inserter = id_to_map_.insert(std::make_pair(tmp.map.map_id(), tmp));
  return (inserter.first -> second.map);
}
inline const Map::Target World::GetTarget(Map& map, const Point& pos) {
  Map::Target ret = map.portal_target(pos);
  if (ret.map == nullptr) {
    ret.map = &NewMap();
    ret.pos = ret.map -> PickARandomPointInGroundOrPath(
                             *random_gen_);
    map.set_portal_target(pos, ret);
  }
  return ret;
}
inline void World::Arrive(Map& map) {
  auto finder = id_to_map_.find(map.map_id());
  assert((finder != id_to_map_.end()));
  ++(finder -> second.connections_num);
}
inline void World::Left(Map& map) {
  auto finder = id_to_map_.find(map.map_id());
  assert(finder != id_to_map_.end());
  std::cout << finder -> second.connections_num << std::endl;
  if(--(finder -> second.connections_num) <= 0) {
    id_to_map_.erase(finder);
  }
}
#endif  // UNNAMING_GAME_SRC_MAP_WORLD_H_
