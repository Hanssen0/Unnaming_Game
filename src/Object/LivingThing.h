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
#ifndef UNNAMING_GAME_SRC_OBJECT_LIVINGTHING_H_
#define UNNAMING_GAME_SRC_OBJECT_LIVINGTHING_H_
#include "../Map/World.h"
#include "../Map/Map.h"
#include "../Interface/Object.h"
#include <algorithm>
#include <cstdint>
#include <vector>
#include <map>
class LivingThing final : public Object {
 public:
  inline LivingThing(World* const world) : Object() {
    now_world_ = world;
  }
  inline void set_view_dis(const int32_t& d) override;
  inline bool is_viewable(const Point& pos) const override;
  inline World::MemoryOfMap& GetMemory() override;
  inline void GoTo(const Point& des) override;
  inline void Transfer(const Point& des, const Map::BlockType& to) override {
  }
  inline void set_max_energy(const int32_t& e) {
    max_energy_ = e;
    now_energy_ = std::min(now_energy_, max_energy_);
  }
  inline void set_now_energy(const int32_t& e) {
    now_energy_ = std::min(e, max_energy_);
  }
  inline void set_now_world(World* const world) {
    now_world_ = world;
  }
  void UpdateViewable();
  constexpr static int32_t kMaxViewDis =
      (SIZE_MAX > INT32_MAX ? INT32_MAX : SIZE_MAX - 1) >> 1;

 private:
  inline void get_id() override {
    set_id(kLivingThingSize++);
  }
  void UpdateViewAbleOnALine(const Point& end);
  void UpdateMemory();
  static int32_t kLivingThingSize;
  int32_t now_energy_;
  int32_t max_energy_;
  std::vector< std::vector< bool > > is_viewable_;
  World* now_world_;
  World::MemoryOfMap* now_memory_;
};
inline void LivingThing::set_view_dis(const int32_t& d) {
  const int32_t limited_d = std::min(kMaxViewDis, d);
  this -> Object::set_view_dis(limited_d);
  const size_t view_size = (static_cast< size_t >(limited_d) << 1) | 1;
  is_viewable_.resize(view_size);
  for (size_t i = 0; i < view_size; ++i) {
    is_viewable_[i].resize(view_size);
  }
}
inline bool LivingThing::is_viewable(const Point& pos) const {
  const Point target = {pos.x - now_pos().x + view_dis(),
                        pos.y - now_pos().y + view_dis()};
  if (target.x >= static_cast< int32_t >(is_viewable_.size()) ||
      target.y >= static_cast< int32_t >(is_viewable_.size()) ||
      target.x < 0 || target.y < 0) {
    return false;
  }
  return is_viewable_[target.x][target.y];
};
inline World::MemoryOfMap& LivingThing::GetMemory() {
  return now_world_ -> GetMemory(id(), now_map());
}
inline void LivingThing::GoTo(const Point& des) {
  if (des.x > 0 && des.y > 0 &&
      des.x < now_map().width() && des.y < now_map().height()) {
    if(abs(des.x - now_pos().x) + abs(des.y - now_pos().y) <= 1) {
      const int32_t c_m = cost(now_map().block(des)).move;
      if (c_m >= 0 && c_m <= now_energy_) {
        now_energy_ -= c_m;
        set_now_pos(des);
      }
    }
  }
}
#endif  // UNNAMING_GAME_SRC_OBJECT_LIVINGTHING_H_
