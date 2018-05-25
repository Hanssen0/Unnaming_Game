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
#ifndef UNNAMING_GAME_SRC_LOGIC_BUILDERINPUT_H_
#define UNNAMING_GAME_SRC_LOGIC_BUILDERINPUT_H_
#include "../Map/Map.h"
#include "../Interface/Random.h"
#include <cstdint>
#include <vector>
class MapBuilder {
 public:
  MapBuilder(UniformIntRandom& ran, const Rect min_room_size,
             const Rect max_room_size) :
      random_gen_(&ran), min_room_size_(min_room_size),
      max_room_size_(max_room_size)  {
  }
  // Make rooms
  void BuildRoomsAndPath();
  //void BuildBuildings();
  inline void set_target_map(const Map& target);

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
  UniformIntRandom* const random_gen_;
  const Rect min_room_size_;
  const Rect max_room_size_;
  // To speed up empty test
  std::vector< std::vector< Rect > > checked_build_able_;
  Map* target_map_;
};
inline void MapBuilder::set_target_map(const Map& target) {
  target_map_ = const_cast< Map* >(&target);
  checked_build_able_.resize(target.width()); 
  for (int32_t i = 0; i < target.width(); ++i) {
    checked_build_able_[i].resize(target.height());
  }
}
#endif  // UNNAMING_GAME_SRC_LOGIC_BUILDERLOGIC_H_
