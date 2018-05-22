#ifndef UNNAMING_GAME_SRC_MAP_WORLD_H_
#define UNNAMING_GAME_SRC_MAP_WORLD_H_
#include "Map.h"
#include <map>
#include <iostream>
class World {
 public:
  World(std::default_random_engine& ran, MapBuilder& builder) :
      builder_(&builder), random_gen_(&ran){
  }
  ~World() {
    for (auto i = link_num_.begin(); i != link_num_.end(); ++i) {
      delete i -> first;
    }
  }
  inline Map* NewMap() {
    Map* ret = new Map(32, 32);
    ret -> FillWith(Map::kBlockWall);
    builder_ -> set_target_map(*ret);
    builder_ -> BuildRoomsAndPath();
    link_num_[ret] = 0;
    return ret;
  }
  inline const Map::Target GetTarget(Map& map, const Point& pos) {
    Map::Target ret = map.portal_target(pos);
    if (ret.map == nullptr) {
      ret.map = NewMap();
      ret.pos = ret.map -> PickARandomPointInGroundOrPath(
                               *random_gen_);
      map.set_portal_target(pos, ret);
    }
    return ret;
  }
  inline void Left(const Map& map) {
    auto finder = link_num_.find(const_cast< Map* >(&map));
    --(finder -> second);
    if (finder -> second == 0) {
      delete (finder -> first);
      link_num_.erase(finder);
    }
  }
  inline void Arrive(const Map& map) {
    ++link_num_[const_cast< Map* >(&map)];
  }

 private:
  std::map< Map*, int > link_num_;
  MapBuilder* const builder_;
  std::default_random_engine* const random_gen_;
};
#endif  // UNNAMING_GAME_SRC_MAP_WORLD_H_
