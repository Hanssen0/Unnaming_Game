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
#include "../Map/Map.h"
#include "../Map/World.h"
#include "Creature.h"
#include <cmath>
#include <creature_export.h>
#include <functional>
#include <queue>
int32_t Creature::kCreatureSize = 0;
constexpr int32_t Creature::kMaxViewDis;
CREATURE_NO_EXPORT inline int64_t Square(const int32_t& in) {
  return static_cast< int64_t >(in) * static_cast< int64_t >(in);
}
// Both a and b should be positive
CREATURE_NO_EXPORT inline int32_t GetDifference(const int32_t& a,
                                                const int32_t& b) {
  if (a > b) return a - b;
  return b - a;
}
// All a, b and c should be positive
CREATURE_NO_EXPORT inline bool IsAPlusBBiggerThanC(int64_t a, int64_t b,
                                                   int64_t c) {
  if (a > c || b > c) return true;
  return b > (c - a);
}
CREATURE_NO_EXPORT int32_t RoundingOfAMulBDivideC(int32_t a, int32_t b,
                                                  int32_t c) {
  if (c == 0) return INT32_MAX;
  bool is_positive = true;
  if (a < 0) {
    is_positive = !is_positive;
    a = -a;
  }
  if (b < 0) {
    is_positive = !is_positive;
    b = -b;
  }
  if (c < 0) {
    is_positive = !is_positive;
    c = -c;
  }
  uint64_t tmp = a * 10;
  tmp *= b;
  tmp /= c;
  if (tmp % 10 < 5) {
    tmp /= 10;
  } else {
    tmp /= 10;
    tmp += 1;
  }
  return (is_positive ? 1 : -1) * tmp;
}
CREATURE_EXPORT Creature::CostOfBlock_ref Creature::CostOfBlock::Create() {
  return CostOfBlock_ref(new CostOfBlock());
}
CREATURE_EXPORT Creature::CostOfBlock& Creature::CostOfBlock::operator=(
    const Creature::CostOfBlock& a) {
  destory_ = a.destory_;
  move_ = a.move_;
  see_through_ = a.see_through_;
  return *this;
}
CREATURE_EXPORT void Creature::CostOfBlock::BindDestoryCost(
    const std::function< int32_t() >& function) {
  destory_ = function;
}
CREATURE_EXPORT void Creature::CostOfBlock::BindMoveCost(
    const std::function< int32_t() >& function) {
  move_ = function;
}
CREATURE_EXPORT void Creature::CostOfBlock::BindSeeThroughCost(
    const std::function< int32_t() >& function) {
  see_through_ = function;
}
CREATURE_NO_EXPORT int32_t Creature::CostOfBlock::DestoryCost() const {
  return destory_();
}
CREATURE_NO_EXPORT int32_t Creature::CostOfBlock::MoveCost() const {
  return move_();
}
CREATURE_NO_EXPORT int32_t Creature::CostOfBlock::SeeThroughCost() const {
  return see_through_();
}
CREATURE_NO_EXPORT Creature::CostOfBlock::CostOfBlock() {};
CREATURE_EXPORT Creature_ref Creature::CreateCreature() {
  return Creature_ref(new Creature());
}
CREATURE_EXPORT Creature_ref Creature::CreateCreature(World* const world) {
  return Creature_ref(new Creature(world));
}
CREATURE_EXPORT void Creature::set_now_map(Map* const map) {now_.map = map;}
CREATURE_EXPORT Map& Creature::now_map() const {return *now_.map;}
CREATURE_EXPORT void Creature::set_now_position(const Point& position) {
  now_.position = position;
}
template <int32_t x, int32_t y>
CREATURE_NO_EXPORT void Creature::Move() {
  Point des = now_position();
  des.x += x;
  des.y += y;
  const int32_t c_m = information_.cost[now_map().block(des)] -> MoveCost();
  if (c_m < 0 || c_m > ability_.now_energy) return;
  ability_.now_energy -= c_m;
  set_now_position(des);
}
constexpr Point kWASD[4] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
//   W         UP
// A S D Left Down Right
template CREATURE_EXPORT void Creature::Move<kWASD[0].x, kWASD[0].y>();
template CREATURE_EXPORT void Creature::Move<kWASD[1].x, kWASD[1].y>();
template CREATURE_EXPORT void Creature::Move<kWASD[2].x, kWASD[2].y>();
template CREATURE_EXPORT void Creature::Move<kWASD[3].x, kWASD[3].y>();
CREATURE_EXPORT const Point& Creature::now_position() const {
  return now_.position;
}
CREATURE_EXPORT void Creature::set_now_world(World* const world) {
  now_.world = world;
}
CREATURE_EXPORT void Creature::set_view_dis(const int32_t& d) {
  ability_.view_dis = std::min(kMaxViewDis, d);
  const size_t view_size = ((ability_.view_dis << 1) | 1);
  information_.is_viewable.resize(view_size);
  for (size_t i = 0; i < view_size; ++i) {
    information_.is_viewable[i].resize(view_size);
  }
}
CREATURE_EXPORT int32_t Creature::view_dis() const {return ability_.view_dis;} 
CREATURE_EXPORT void Creature::UpdateViewable() {
  const size_t dis_array_size = information_.is_viewable.size();
  std::vector< std::vector< bool > > is_tested(dis_array_size, 
                                               std::vector< bool >(
                                                   dis_array_size,
                                                   false));
  std::queue< Point > waiting;
  is_tested[view_dis()][view_dis()] = true;
  waiting.push({view_dis(), view_dis()});
  for (size_t i = 0; i < dis_array_size; ++i) {
    for (size_t j = 0; j < dis_array_size; ++j) {
      information_.is_viewable[i][j] = false;
    }
  }
  information_.is_viewable[view_dis()][view_dis()] = true;
  // Prevent additional computation
  const int32_t min_x = now_position().x < view_dis() ?
                            view_dis() - now_position().x : 0;
  const int32_t min_y = now_position().y < view_dis() ?
                            view_dis() - now_position().y : 0;
  const int32_t max_x = now_position().x + view_dis() >= now_map().width() ?
                            view_dis() +
                                (now_map().width() - 1 - now_position().x) :
                            dis_array_size - 1;
  const int32_t max_y = now_position().y + view_dis() >= now_map().height() ?
                            view_dis() +
                                (now_map().height() - 1 - now_position().y) :
                            dis_array_size - 1;
  int64_t square_view_dis = Square(view_dis());
  while (!waiting.empty()) {
    Point tmp = waiting.front();
    waiting.pop();
    if (IsAPlusBBiggerThanC(Square(GetDifference(tmp.x, view_dis())),
                            Square(GetDifference(tmp.y, view_dis())),
                            square_view_dis)) continue;
    //Four directions
    for (int32_t i = 0; i < 4; ++i) {
      tmp.x += kWASD[i].x;
      tmp.y += kWASD[i].y;
      if (tmp.x >= min_x && tmp.y >= min_y &&
          tmp.x <= max_x && tmp.y <= max_y && (!is_tested[tmp.x][tmp.y])) {
        waiting.push(tmp);
        is_tested[tmp.x][tmp.y] = true;
      }
      tmp.x -= kWASD[i].x;
      tmp.y -= kWASD[i].y;
    }
    tmp.x -= view_dis();
    tmp.y -= view_dis();
    UpdateViewAbleOnALine(tmp);
  }
  UpdateMemory();
}
CREATURE_EXPORT bool Creature::is_viewable(const Point& pos) const {
  const Point target = {pos.x - now_position().x + view_dis(),
                        pos.y - now_position().y + view_dis()};
  const int32_t viewable_size = information_.is_viewable.size();
  if (target.x >= viewable_size || target.y >= viewable_size ||
      target.x < 0 || target.y < 0) return false;
  return information_.is_viewable[target.x][target.y];
};
CREATURE_EXPORT int32_t Creature::id() {
  if (!information_.is_have_id) get_id();
  return information_.id;
}
CREATURE_EXPORT void Creature::set_max_energy(const int32_t& energy) {
  ability_.max_energy = energy;
  ability_.now_energy = std::min(ability_.now_energy, ability_.max_energy);
}
CREATURE_EXPORT void Creature::set_now_energy(const int32_t& energy) {
  ability_.now_energy = std::min(energy, ability_.max_energy);
}
CREATURE_EXPORT void Creature::set_cost(const Map::BlockType& type,
                                        const CostOfBlock& cost) {
  information_.cost[type] = &cost;
}
CREATURE_EXPORT World::MemoryOfMap& Creature::GetMemory() {
  return now_.world -> GetMemory(id(), now_map());
}
CREATURE_NO_EXPORT Creature::Creature() {information_.is_have_id = false;}
CREATURE_NO_EXPORT Creature::Creature(World* const world) {
  now_.world = world;
  information_.is_have_id = false;
}
CREATURE_NO_EXPORT void Creature::get_id() {information_.id = kCreatureSize++;}
CREATURE_NO_EXPORT void Creature::UpdateViewAbleOnALine(const Point& end) {
  const int32_t* max_det;
  const int32_t* min_det;
  int i;
  int result;
  int32_t* testing_x;
  int32_t* testing_y;
  int32_t positive;
  if (std::abs(end.x) > std::abs(end.y)) {
    max_det = &(end.x);
    min_det = &(end.y);
    testing_x = &i;
    testing_y = &result;
  } else {
    max_det = &(end.y);
    min_det = &(end.x);
    testing_x = &result;
    testing_y = &i;
  }
  positive = (*max_det) < 0 ? -1 : 1;
  int32_t energy = view_dis();
  for (i = positive; i != ((*max_det) + positive); i += positive) {
    result = RoundingOfAMulBDivideC(i , *min_det, *max_det);
    information_.is_viewable[view_dis() + *testing_x]
                            [view_dis() + *testing_y] = true;
    const int32_t c_s =
        information_.cost[now_map().block(
                                        {now_position().x + *testing_x,
                                         now_position().y + *testing_y})
                         ] -> SeeThroughCost();
    if (c_s < 0) break;
    energy -= c_s;
    if (energy <= 0) break;
  }
}
CREATURE_NO_EXPORT void Creature::UpdateMemory() {
  World::MemoryOfMap& now_mem = GetMemory();
  for (size_t i = 0; i < information_.is_viewable.size(); ++i) {
    for (size_t j = 0; j < information_.is_viewable.size(); ++j) {
      if (information_.is_viewable[i][j]) {
        const Point tmp = {now_position().x - view_dis() +
                           static_cast< int32_t >(i),
                           now_position().y - view_dis() +
                           static_cast< int32_t >(j)};
        now_mem.left_top.x = std::min(now_mem.left_top.x, tmp.x);
        now_mem.left_top.y = std::min(now_mem.left_top.y, tmp.y);
        now_mem.right_bottom.x = std::max(now_mem.right_bottom.x, tmp.x);
        now_mem.right_bottom.y = std::max(now_mem.right_bottom.y, tmp.y);
        now_mem.is_seen[tmp.x][tmp.y] = true;
        now_mem.detail.set_block(tmp, now_map().block(tmp));
      }
    }
  }
}
