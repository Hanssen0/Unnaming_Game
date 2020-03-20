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
#ifndef UNNAMING_GAME_SRC_LOGIC_PATHFINDER_H_
#define UNNAMING_GAME_SRC_LOGIC_PATHFINDER_H_
#include <cstdint>
#include <list>
#include <map>
#include <vector>
#include "../Map/Map.h"
class PathFinder {
 public:
  std::list< Point > FindShortestPath(const Point& from, const Point& to);
  inline void set_value(const BlockPtr& type, int value);
  void set_target_map(const Map& target);

 private:
  struct AstarStat {
    Point self;
    PathFinder* original_finder;
  };
  void UpdateNearby(const Point& now);
  bool TryAPoint(const BlockPtr& type, uint64_t walked_dis,
                 const Point& now);
  void PushPointToAstarList(const Point&);
  std::vector<int> value_;
  // A star data
  std::vector< std::vector< bool > > walked_;
  std::vector< std::vector< uint64_t > > walked_dis_;
  std::vector< std::vector< bool > > is_first_check_;
  std::vector< std::vector< Point > > father_;
  std::list< Point > searching_list;
  const Map* target_map_;
};
inline void PathFinder::set_value(const BlockPtr& type, int value) {
  const auto block_size = Block::BlockSize();
  if (value_.size() < block_size) value_.resize(block_size);
  value_[type->index()] = value;
}
#endif  // UNNAMING_GAME_SRC_LOGIC_PATHFINDER_H_
