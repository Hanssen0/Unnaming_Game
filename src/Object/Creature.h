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
#include <memory>
#include <vector>
#include "../Map/Space.h"
#include "../Map/Map.h"
#include "../Fov/shadowcasting.h"
class Creature;
typedef std::shared_ptr< Creature > Creature_ref;
class Creature {
 public:
  class CostOfBlock;
  typedef std::shared_ptr< CostOfBlock > CostOfBlock_ref;
  class CostOfBlock {
   public:
    static CostOfBlock_ref Create();
    CostOfBlock& operator=(const CostOfBlock& a);
    void BindDestoryCost(const std::function< int32_t() >& function);
    void BindMoveCost(const std::function< int32_t() >& function);
    void BindSeeThroughCost(const std::function< int32_t() >& function);
    int32_t DestoryCost() const;
    int32_t MoveCost() const;
    int32_t SeeThroughCost() const;
    ~CostOfBlock();

   private:
    CostOfBlock();
    std::function< int32_t() > destory_;
    std::function< int32_t() > move_;
    std::function< int32_t() > see_through_;
  };
  static Creature_ref Create(Space* const space);
  int32_t id();
  Map* map() const;
  const Point& position() const;
  int32_t view_dis() const;
  void set_cost(const BlockPtr& type, const CostOfBlock_ref& cost);
  void set_max_energy(const int32_t& energy);
  void set_now_energy(const int32_t& energy);
  void set_view_dis(const int32_t& d);
  ~Creature();
  bool is_viewable(const Point& pos) const;
  void Destory(const Point&);
  Space::MemoryOfMap& GetMemory();
  template <int32_t x, int32_t y> void Move();
  void Teleport(Map* const, const Point&);
  void UpdateViewable();
  constexpr static int32_t kMaxViewDis =
      (SIZE_MAX > INT32_MAX ? INT32_MAX : SIZE_MAX - 1) >> 1;

 private:
  explicit Creature(Space* const space);
  Creature& operator=(const Creature&) = delete;
  void get_id();
  void UpdateMemory();
  static int32_t kCreatureSize;
  Map* map_;
  Point position_;
  struct {
    Space* space;
    Space::MemoryOfMap* memory;
  } now_;
  struct {
    int32_t view_dis;
    int32_t now_energy;
    int32_t max_energy;
  } ability_;
  struct {
    int32_t id;
    bool is_have_id;
    std::vector< CostOfBlock_ref > cost;
    std::vector< std::vector< bool > > is_viewable;
  } information_;
  void set_position(const Point&);
  bool is_valid(const Point& pos);
  void set_viewable(const Point& pos);
  int32_t get_cost(const Point& pos);
  FunctorShadowCasting shadow_casting = FunctorShadowCasting()
    .SetFunction_IsValid(
      std::bind(&Creature::is_valid, this, std::placeholders::_1))
    .SetFunction_SetViewable(
      std::bind(&Creature::set_viewable, this, std::placeholders::_1))
    .SetFunction_GetCost(
      std::bind(&Creature::get_cost, this, std::placeholders::_1));
};
#endif  // UNNAMING_GAME_SRC_OBJECT_CREATURE_H_
