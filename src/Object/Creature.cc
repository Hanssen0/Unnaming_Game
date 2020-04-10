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
#include "./Action/creature_action_implementation.h"
#include "../Map/Building/BaseBuilding.h"
#include "../Map/Map.h"
#include "../Map/Space.h"
size_t Creature::kCreatureSize = 0;
template<int x, int y> void Creature::Perform(const Action& action) {
  MapPoint des = position();
  des += IntPoint(x, y);
  action.Perform(this->map(), des, this);
}
CREATURE_NO_EXPORT Creature::Creature() {information_.id = kCreatureSize++;}
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
  return map_->has(pos) ?
      map()->GroundIn(pos).CostSeeThrough(*this) : 0x3f3f3f3f;
}
constexpr int kWASD[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
//   W         UP
// A S D Left Down Right
template CREATURE_EXPORT void Creature::Perform<kWASD[0][0], kWASD[0][1]>(
    const Action&);
template CREATURE_EXPORT void Creature::Perform<kWASD[1][0], kWASD[1][1]>(
    const Action&);
template CREATURE_EXPORT void Creature::Perform<kWASD[2][0], kWASD[2][1]>(
    const Action&);
template CREATURE_EXPORT void Creature::Perform<kWASD[3][0], kWASD[3][1]>(
    const Action&);
CREATURE_EXPORT Creature_ref Creature::Create() {
  return Creature_ref(new Creature());
}
CREATURE_EXPORT void Creature::Obtain(const Item& item) {
  items_.push_back(item);
}
CREATURE_EXPORT void Creature::SetPosition(const MapPoint& pos) {
  position_ = pos;
}
CREATURE_EXPORT void Creature::Teleport(const Map_ref& map,
                                        const MapPoint& pos) {
  map->Link();
  if (map_) map_->Unlink();
  map_ = map;
  SetPosition(pos);
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
CREATURE_EXPORT const size_t& Creature::Index() const {
  return information_.id;
}
CREATURE_EXPORT void Creature::set_max_energy(const int& energy) {
  ability_.max_energy = energy;
  ability_.now_energy = std::min(ability_.now_energy, ability_.max_energy);
}
CREATURE_EXPORT void Creature::set_now_energy(const int& energy) {
  ability_.now_energy = std::min(energy, ability_.max_energy);
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
