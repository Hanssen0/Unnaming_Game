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
#ifndef UNNAMING_GAME_SRC_OBJECT_CREATURE_H_
#define UNNAMING_GAME_SRC_OBJECT_CREATURE_H_
#include <cstdint>
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <vector>
#include "../Item/Item.h"
#include "../Map/Space.h"
#include "../Map/Map.h"
#include "../Fov/shadowcasting.h"
class Creature;
typedef std::shared_ptr< Creature > Creature_ref;
class Creature {
 public:
  class Action;
  struct Memory {
    MapPoint left_top;
    MapPoint right_bottom;
    std::vector< std::vector<bool> > is_seen;
    Map_ref detail;
  };
  static Creature_ref Create();
  const size_t& Index() const;
  size_t view_dis() const;
  const Map_ref& map() const;
  const MapPoint& position() const;
  void set_max_energy(const int& energy);
  void set_now_energy(const int& energy);
  void SetViewDis(const size_t& d);
  ~Creature();
  bool is_viewable(const MapPoint& pos) const;
  template<int, int> void Perform(const Action&);
  Memory& GetMemory();
  void Interact();
  void Obtain(const Item&);
  void SetPosition(const MapPoint&);
  void Teleport(const Map_ref&, const MapPoint&);
  void UpdateViewable();

 private:
  Creature();
  Creature& operator=(const Creature&) = delete;
  void UpdateMemory();
  static size_t kCreatureSize;
  Map_ref map_;
  MapPoint position_;
  struct {
    size_t view_dis;
    int now_energy;
    int max_energy;
  } ability_;
  struct {
    size_t id;
    std::vector< std::vector< bool > > is_viewable;
  } information_;
  std::list<Item> items_;
  std::map<size_t, Memory> memories_;
  bool is_valid(const MapPoint& pos) const;
  void set_viewable(const MapPoint& pos);
  int get_cost(const MapPoint& pos);
  FunctorShadowCasting shadow_casting = FunctorShadowCasting()
    .SetFunction_IsValid(
      std::bind(&Creature::is_valid, this, std::placeholders::_1))
    .SetFunction_SetViewable(
      std::bind(&Creature::set_viewable, this, std::placeholders::_1))
    .SetFunction_GetCost(
      std::bind(&Creature::get_cost, this, std::placeholders::_1));
};
#endif  // UNNAMING_GAME_SRC_OBJECT_CREATURE_H_
