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
#include "../Map/Map.h"
#include "../Interface/Object.h"
#include <algorithm>
#include <cstdint>
#include <vector>
class LivingThing final : public Object {
 public:
  inline void set_view_dis(const int32_t& d) override;
  inline bool is_viewable(const Point& pos) const override {
  }
  inline MemoryOfMap& GetMemory() override {
  }
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
  void UpdateViewable();

 private:
  int32_t now_energy_;
  int32_t max_energy_;
  std::vector< std::vector< bool > > is_viewable_;
};
inline void set_view_dis(const int32_t& d) {
  Object::set_view_dis(d);
  is_viewable_.resize(d);
  for (int32_t i = 0; i < d; ++i) {
    is_viewable_[i].resize(d);
  }
}
inline void GoTo(const Point& des) override {
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
