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
#include "./Block.h"
#include "./Building/Building.h"
#include "./Map.h"
#include "../Logic/MapBuilder.h"
class Space {
 public:
  inline Space(MapBuilder* builder, const Rect& nms,
               const BlockPtr& empty_block) : builder_(builder),
      empty_block_(empty_block), next_map_size_(nms) {}
  inline void set_empty_block(const BlockPtr& block) {empty_block_ = block;}
  inline void set_empty_building(const Building& building) {
    empty_building_ = &building;
  }
  inline const BlockPtr& empty_block() const {return empty_block_;}
  inline const Building& empty_building() const {return *empty_building_;}
  inline void set_next_map_size(const Rect& si) {next_map_size_ = si;}
  inline Map_ref NewMap();

 private:
  MapBuilder* const builder_;
  BlockPtr empty_block_;
  const Building* empty_building_;
  std::list<Map_ref> maps_;
  Rect next_map_size_;
};
inline Map_ref Space::NewMap() {
  Map_ref tmp = Map::Create(next_map_size_);
  maps_.push_front(tmp);
  auto map_iterator = maps_.begin();
  tmp->SetDestory([map_iterator, this](){maps_.erase(map_iterator);});
  tmp->SetEmptyBlock(empty_block_);
  builder_->set_target_map(tmp.get());
  builder_->Build();
  return tmp;
}
#endif  // UNNAMING_GAME_SRC_MAP_SPACE_H_
