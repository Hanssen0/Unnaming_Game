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
#include <list>
#include <iostream>
#include <functional>
#include <random>
#include "Map/Building/BaseBuilding.h"
#include "Map/Map.h"
#include "Logic/MapBuilder.h"
#include "Object/Creature.h"
#include "FrontEnd/CinInput.h"
#include "Graphic/Renderer.h"
#include "Map/Space.h"
Renderer_ref kMainRenderer = Renderer::Create();
// TODO(handsome0hell): Read block from file
auto ground = Block::Create();
auto path = Block::Create();
auto wall = Block::Create();
auto empty = BaseBuilding();
auto portal = BaseBuilding();
auto empty_building = static_cast<Building>(empty);
auto portal_building = static_cast<Building>(portal);
void Init(Creature* role) {
  Creature::CostOfBlock_ref normal_cost = Creature::CostOfBlock::Create();
  Creature::CostOfBlock_ref stop_cost = Creature::CostOfBlock::Create();
  normal_cost->BindMoveCost([]()->int {return 1;});
  normal_cost->BindSeeThroughCost([]()->int {return 0;});
  role->set_cost(path, normal_cost);
  role->set_cost(ground, normal_cost);
  stop_cost->BindMoveCost([]()->int {return -1;});
  stop_cost->BindSeeThroughCost([]()->int {return 0x3f3f3f3f;});
  role->set_cost(wall, stop_cost);
  role->set_max_energy(10);
  role->set_now_energy(10);
  role->set_view_dis(6);
  // TODO(handsome0hell): Read block from file
  kMainRenderer->set_exterior_of_block('#', wall);
  kMainRenderer->set_exterior_of_block('.', ground);
  kMainRenderer->set_exterior_of_block('+', path);
  kMainRenderer->set_exterior_of_building('0', portal_building);
}
class AutoResetStatus {
 public:
  inline AutoResetStatus() : status_(false) {}
  inline void set_status() {status_ = true;}
  inline bool Status() {
    const bool tmp = status_;
    status_ = false;
    return tmp;
  }
 private:
  bool status_;
};
int main() {
  std::default_random_engine random_engine;
  std::uniform_int_distribution<size_t> rand_dis;
  random_engine.seed(static_cast<unsigned int>(time(0)));
  std::function<size_t(size_t, size_t)> GenerateRandom =
      [&random_engine, &rand_dis](size_t from, size_t to) {
        return rand_dis(random_engine,
                        std::uniform_int_distribution<size_t>::param_type(from,
                                                                          to));
      };
  MapBuilder builder(GenerateRandom, {3, 3}, {8, 8});
  builder.SetGroundBlock(ground);
  builder.SetPathBlock(path);
  builder.SetWallBlock(wall);
  builder.SetEmptyBuilding(empty_building);
  builder.SetPortalBuilding(portal_building);
  Space main_space(&builder, {32, 32}, ground);
  Creature_ref main_role = Creature::Create();
  Init(main_role.get());
  // TODO(handsome0hell): Read block from file
  std::list<BlockPtr> valid;
  valid.push_back(path);
  valid.push_back(ground);
  auto new_map = main_space.NewMap();
  main_role->Teleport(new_map,
                      new_map->PickRandomPointIn(GenerateRandom, valid));
  AutoResetStatus null_status;
  CinInput_ref input =
      CinInput::CreateCinInput([&null_status](){null_status.set_status();});
  AutoResetStatus quit_status;
  AutoResetStatus new_map_status;
  AutoResetStatus render_memory_status;
  input->BindKey('w', [&main_role](){main_role->Move< 0, -1 >();});
  input->BindKey('a', [&main_role](){main_role->Move< -1, 0 >();});
  input->BindKey('s', [&main_role](){main_role->Move< 0, 1 >();});
  input->BindKey('d', [&main_role](){main_role->Move< 1, 0 >();});
  input->BindKey('i', [&main_role](){main_role->Destroy< 0, -1 >();});
  input->BindKey('j', [&main_role](){main_role->Destroy< -1, 0 >();});
  input->BindKey('k', [&main_role](){main_role->Destroy< 0, 1 >();});
  input->BindKey('l', [&main_role](){main_role->Destroy< 1, 0 >();});
  input->BindKey('q', [&quit_status](){quit_status.set_status();});
  input->BindKey('m', [&render_memory_status](){
                            render_memory_status.set_status();
                         });
  input->BindKey('n', [&new_map_status](){new_map_status.set_status();});
  bool is_init_stat = true;
  while (!quit_status.Status()) {
    if (is_init_stat) {
      is_init_stat = false;
    } else {
      input->HandleInput();
    }
    if (!null_status.Status()) {
      // TODO(handsome0hell): Finish energy system
      main_role->set_now_energy(10);
      if (new_map_status.Status()) {
        if (main_role->map()->
            BuildingIn(main_role->position()).index() ==
            portal_building.index()) {
          new_map = main_space.NewMap();
          main_role->Teleport(
              new_map, new_map->PickRandomPointIn(GenerateRandom, valid));
        }
      }
      main_role->UpdateViewable();
      system("clear");
      if (render_memory_status.Status()) {
        kMainRenderer->RenderMemory(main_role->GetMemory());
      } else {
        kMainRenderer->RenderCreaturesView(*main_role);
      }
      std::cout << std::flush;
    }
  }
}
