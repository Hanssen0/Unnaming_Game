#ifndef UNNAMING_GAME_SRC_MAP_WORLD_H_
#define UNNAMING_GAME_SRC_MAP_WORLD_H_
#include "GameMap.h"
#include <map>
#include <iostream>
class World {
 public:
  inline GameMap * NewMap() {
    GameMap * ret = new GameMap;
    builder_ -> set_target_map(ret);
    builder_ -> CleanMap();
    builder_ -> BuildRoomsAndPath();
    builder_ -> BuildBuildings();
    link_num_[ret] = 0;
    return ret;
  }
  inline GameMap::TargetInMap * GetTarget(GameMap * map, const Point & pos) {
    GameMap::TargetInMap * ret = map -> portal_target(pos);
    if (ret == nullptr) {
      GameMap::TargetInMap tmp;
      tmp.target_map = NewMap();
      tmp.target_pos = tmp.target_map -> PickARandomPointInGroundOrPath(
                           random_gen_);
      map -> set_portal_target(pos, tmp);
      ret = map -> portal_target(pos);
    }
    return ret;
  }
  inline void Left(const GameMap * map) {
    auto finder = link_num_.find(const_cast< GameMap * >(map));
    std::cout << "Minus" << --(finder -> second) << std::endl;
    std::cin.get();
    if (finder -> second == 0) {
      delete (finder -> first);
      link_num_.erase(finder);
      std::cout << "DELETED" << std::endl;
      std::cin.get();
    }
  }
  inline void Arrive(const GameMap * map) {
    std::cout << "ADD" << ++link_num_[const_cast< GameMap * >(map)] << std::endl;
      std::cin.get();
  }
  inline void set_builder(const GameMapBuilder * builder) {
    builder_ = const_cast< GameMapBuilder * >(builder);
  }
  inline void set_random_gen(const RandomGenerater * ran) {
    random_gen_ = const_cast< RandomGenerater * >(ran);
  }
  inline void Test() {
    for (auto i = link_num_.begin(); i != link_num_.end(); ++i) {
      std::cout << i -> second << std::endl;
    }
  }
  ~World() {
    for (auto i = link_num_.begin(); i != link_num_.end(); ++i) {
      delete i -> first;
      std::cout << "D!" << std::endl;
    }
  }
  World() {
    builder_ = nullptr;
  }

 private:
  std::map< GameMap *, int > link_num_;
  GameMapBuilder * builder_;
  RandomGenerater * random_gen_;
};
#endif  // UNNAMING_GAME_SRC_MAP_WORLD_H_