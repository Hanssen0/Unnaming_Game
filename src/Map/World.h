#ifndef UNNAMING_GAME_SRC_MAP_WORLD_H_
#define UNNAMING_GAME_SRC_MAP_WORLD_H_
#include "Map.h"
#include "../Interface/Random.h"
#include <map>
class World {
 public:
  World(UniformIntRandom& ran, MapBuilder& builder) :
      builder_(&builder), random_gen_(&ran){
  }
  ~World();
  inline Map* NewMap();
  inline const Map::Target GetTarget(Map& map, const Point& pos);
  inline void DisConnect(Map& map);
  inline void Connect(Map& map);

 private:
  std::map< int32_t, std::pair< int32_t, Map* > > connections_num_and_map_;
  MapBuilder* const builder_;
  UniformIntRandom* const random_gen_;
};
World::~World() {
  for (auto i = connections_num_and_map_.begin();
       i != connections_num_and_map_.end(); ++i) {
    delete i -> second.second;
  }
}
inline Map* World::NewMap() {
  Map* ret = new Map(32, 32);
  ret -> get_id();
  ret -> FillWith(Map::kBlockWall);
  builder_ -> set_target_map(*ret);
  builder_ -> BuildRoomsAndPath();
  connections_num_and_map_[ret -> map_id()] = std::make_pair(0, ret);
  return ret;
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
inline void World::DisConnect(Map& map) {
  auto finder = connections_num_and_map_.find(map.map_id());
  --(finder -> second.first);
  if (finder -> second.first == 0) {
    delete (finder -> second.second);
    connections_num_and_map_.erase(finder);
  }
}
inline void World::Connect(Map& map) {
  ++connections_num_and_map_[map.map_id()].first;
}
#endif  // UNNAMING_GAME_SRC_MAP_WORLD_H_
