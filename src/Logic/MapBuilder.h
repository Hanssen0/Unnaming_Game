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
#ifndef UNNAMING_GAME_SRC_LOGIC_MAPBUILDER_H_
#define UNNAMING_GAME_SRC_LOGIC_MAPBUILDER_H_
#include <cstdint>
#include <algorithm>
#include <functional>
#include <vector>
#include "../Map/Map.h"
class MapBuilder {
 public:
  MapBuilder(const std::function<size_t(size_t, size_t)>& ran,
             const Rect min_room_size, const Rect max_room_size) :
      random_gen_(ran), min_room_size_(min_room_size),
      max_room_size_(max_room_size)  {
  }
  ~MapBuilder();
  // Make rooms
  void Build();
  // void BuildBuildings();
  inline void set_target_map(Map* const target);
  void SetWallBlock(const Building& wall);
  void SetPathBlock(const Building& path);
  void SetGroundBlock(const Building& ground);
  void SetEmptyBuilding(const Building& empty);
  void SetPortalBuilding(const Building& portal);

 private:
  // Init to speed up empty test
  void InitForEmptyTest();
  // Update array to speed up empty test
  void UpdateCheckedBuildAble(const MapPoint& pos_to_update);
  // Build path by A*
  void BuildPath(const MapPoint& from, const MapPoint& to);
  bool SelectRoomPosition(Map::RectWithPos*);
  // Build one room
  bool BuildRoom(MapPoint* room_pos);
  bool IsRectEmpty(const Map::RectWithPos& rect_for_check);
  inline Rect RandomRoomRect();
  const std::function<size_t(size_t, size_t)> random_gen_;
  const Rect min_room_size_;
  const Rect max_room_size_;
  // To speed up empty test
  std::vector< std::vector< Rect > > checked_build_able_;
  Map* target_map_;
  Building wall_block_;
  Building path_block_;
  Building ground_block_;
  Building empty_building_;
  Building portal_building_;
};
inline void MapBuilder::set_target_map(Map* const target) {
  target_map_ = target;
  checked_build_able_.resize(target_map_->Width());
  for (size_t i = 0; i < target_map_->Width(); ++i) {
    checked_build_able_[i].resize(target_map_->Height());
  }
}
#endif  // UNNAMING_GAME_SRC_LOGIC_MAPBUILDER_H_
