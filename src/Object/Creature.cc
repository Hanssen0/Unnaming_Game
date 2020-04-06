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
#include "Creature.h"
#include <algorithm>
#include <cmath>
#include <functional>
#include <queue>
#include <utility>
#include "./creature_cmake.h"
#include "../Map/Building/BaseBuilding.h"
#include "../Map/Map.h"
#include "../Map/Space.h"
size_t Creature::kCreatureSize = 0;
// Creature::CostofBlock
CREATURE_NO_EXPORT int Creature::CostOfBlock::DestroyCost() const {
  return destroy_();
}
CREATURE_NO_EXPORT int Creature::CostOfBlock::MoveCost() const {
  return move_();
}
CREATURE_NO_EXPORT int Creature::CostOfBlock::SeeThroughCost() const {
  return see_through_();
}
CREATURE_NO_EXPORT Creature::CostOfBlock::CostOfBlock() {}
CREATURE_EXPORT Creature::CostOfBlock_ref Creature::CostOfBlock::Create() {
  return CostOfBlock_ref(new CostOfBlock());
}
CREATURE_EXPORT Creature::CostOfBlock& Creature::CostOfBlock::operator=(
    const Creature::CostOfBlock& a) {
  destroy_ = a.destroy_;
  move_ = a.move_;
  see_through_ = a.see_through_;
  return *this;
}
CREATURE_EXPORT void Creature::CostOfBlock::BindDestroyCost(
    const std::function< int() >& function) {
  destroy_ = function;
}
CREATURE_EXPORT void Creature::CostOfBlock::BindMoveCost(
    const std::function< int() >& function) {
  move_ = function;
}
CREATURE_EXPORT void Creature::CostOfBlock::BindSeeThroughCost(
    const std::function< int() >& function) {
  see_through_ = function;
}
CREATURE_EXPORT Creature::CostOfBlock::~CostOfBlock() {}
// Creature
CREATURE_NO_EXPORT void Creature::set_position(const MapPoint& pos) {
  position_ = pos;
}
template<int x, int y> CREATURE_NO_EXPORT void Creature::Move() {
  MapPoint des = position();
  des += IntPoint(x, y);
  if (!map()->has(des)) return;
  const int c_m = information_.cost[map()->GroundIn(des).index()]->MoveCost();
  if (c_m < 0 || c_m > ability_.now_energy) return;
  ability_.now_energy -= c_m;
  set_position(des);
}
template<int x, int y> void Creature::Destroy() {
  MapPoint des = position();
  des += IntPoint(x, y);
  if (!map()->has(des)) return;
  map()->DestroyGroundIn(des);
}
CREATURE_NO_EXPORT Creature::Creature() {information_.is_have_id = false;}
CREATURE_NO_EXPORT void Creature::get_id() {
  information_.is_have_id = true;
  information_.id = kCreatureSize++;
}
CREATURE_NO_EXPORT void Creature::UpdateMemory() {
  Memory& now_mem = GetMemory();
  for (size_t i = 0; i < information_.is_viewable.size(); ++i) {
    for (size_t j = 0; j < information_.is_viewable.size(); ++j) {
      if (information_.is_viewable[i][j]) {
        const MapPoint tmp = position() + MapPoint(i, j) - view_dis();
        now_mem.left_top.x = std::min(now_mem.left_top.x, tmp.x);
        now_mem.left_top.y = std::min(now_mem.left_top.y, tmp.y);
        now_mem.right_bottom.x = std::max(now_mem.right_bottom.x, tmp.x);
        now_mem.right_bottom.y = std::max(now_mem.right_bottom.y, tmp.y);
        now_mem.is_seen[tmp.x][tmp.y] = true;
        now_mem.detail->CopyFromIn(*map(), tmp);
      }
    }
  }
}
CREATURE_NO_EXPORT bool Creature::is_valid(const MapPoint& pos) const {
  MapPoint target = pos + view_dis();
  if (target < position()) return false;
  target -= position();
  const size_t viewable_size = information_.is_viewable.size();
  return target < viewable_size;
}
CREATURE_NO_EXPORT void Creature::set_viewable(const MapPoint& pos) {
  if (!is_valid(pos)) return;
  information_.is_viewable[pos.x - position().x + view_dis()]
                          [pos.y - position().y + view_dis()] = true;
}
CREATURE_NO_EXPORT int Creature::get_cost(const MapPoint& pos) {
  return map_->has(pos)? information_.cost[map()->GroundIn(pos).index()]
                             ->SeeThroughCost() : 0x3f3f3f3f;
}
constexpr int kWASD[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
//   W         UP
// A S D Left Down Right
template CREATURE_EXPORT void Creature::Move<kWASD[0][0], kWASD[0][1]>();
template CREATURE_EXPORT void Creature::Move<kWASD[1][0], kWASD[1][1]>();
template CREATURE_EXPORT void Creature::Move<kWASD[2][0], kWASD[2][1]>();
template CREATURE_EXPORT void Creature::Move<kWASD[3][0], kWASD[3][1]>();
template CREATURE_EXPORT void Creature::Destroy<kWASD[0][0], kWASD[0][1]>();
template CREATURE_EXPORT void Creature::Destroy<kWASD[1][0], kWASD[1][1]>();
template CREATURE_EXPORT void Creature::Destroy<kWASD[2][0], kWASD[2][1]>();
template CREATURE_EXPORT void Creature::Destroy<kWASD[3][0], kWASD[3][1]>();
CREATURE_EXPORT Creature_ref Creature::Create() {
  return Creature_ref(new Creature());
}
CREATURE_EXPORT void Creature::Teleport(const Map_ref& map,
                                        const MapPoint& pos) {
  if (map_) map_->Unlink();
  map->Link();
  map_ = map;
  set_position(pos);
}
CREATURE_EXPORT const Map_ref& Creature::map() const {return map_;}
CREATURE_EXPORT const MapPoint& Creature::position() const {return position_;}
CREATURE_EXPORT void Creature::SetViewDis(const size_t& d) {
  constexpr static size_t kMaxViewDis = (SIZE_MAX - 1) >> 1;
  assert(d <= kMaxViewDis);
  ability_.view_dis = d;
  const size_t view_size = ((ability_.view_dis << 1) | 1);
  information_.is_viewable.resize(view_size);
  for (size_t i = 0; i < view_size; ++i) {
    information_.is_viewable[i].resize(view_size);
  }
}
CREATURE_EXPORT size_t Creature::view_dis() const {return ability_.view_dis;}
CREATURE_EXPORT void Creature::UpdateViewable() {
  const size_t dis_array_size = information_.is_viewable.size();
  for (size_t i = 0; i < dis_array_size; ++i) {
    for (size_t j = 0; j < dis_array_size; ++j) {
      information_.is_viewable[i][j] = false;
    }
  }
  shadow_casting(position(), view_dis());
  UpdateMemory();
}
CREATURE_EXPORT bool Creature::is_viewable(const MapPoint& pos) const {
  if (!map_->has(pos)) return false;
  MapPoint target = pos + view_dis();
  if (target < position()) return false;
  target -= position();
  const size_t viewable_size = information_.is_viewable.size();
  if (target > viewable_size) return false;
  return information_.is_viewable[target.x][target.y];
}
CREATURE_EXPORT size_t Creature::id() {
  if (!information_.is_have_id) get_id();
  return information_.id;
}
CREATURE_EXPORT void Creature::set_max_energy(const int& energy) {
  ability_.max_energy = energy;
  ability_.now_energy = std::min(ability_.now_energy, ability_.max_energy);
}
CREATURE_EXPORT void Creature::set_now_energy(const int& energy) {
  ability_.now_energy = std::min(energy, ability_.max_energy);
}
CREATURE_EXPORT void Creature::set_cost(const Building& type,
                                        const CostOfBlock_ref& cost) {
  const auto block_size = BaseBuilding::BaseBuildingSize();
  if (information_.cost.size() < block_size) {
    information_.cost.resize(block_size);
  }
  information_.cost[type.index()] = cost;
}
CREATURE_EXPORT Creature::~Creature() {}
CREATURE_EXPORT Creature::Memory& Creature::GetMemory() {
  auto memory = memories_.find(map()->Id());
  if (memory == memories_.end()) {
    const Memory tmp = {MapPoint(map()->Width(), map()->Height()), {0, 0},
                             std::vector< std::vector<bool>>(map()->Width(),
                                 std::vector<bool>(map()->Height(), false)),
                             Map::Create(map()->Size())};
    memory = memories_.insert(std::make_pair(map()->Id(), tmp)).first;
  }
  return memory->second;
}
CREATURE_EXPORT void Creature::Interact() {
  map()->BuildingIn(position()).Interact(this);
}
