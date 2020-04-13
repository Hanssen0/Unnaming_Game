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
#include "Object/Action/CreatureActions.h"
#include "Object/Creature.h"
#include "FrontEnd/CinInput.h"
#include "Graphic/Renderer.h"
#include "Map/Space.h"
Renderer_ref kMainRenderer = Renderer::Create();
// TODO(handsome0hell): Read block from file
BaseBuilding ground;
BaseBuilding path;
BaseBuilding wall;
BaseBuilding empty;
BaseBuilding portal;
// TODO(handsome0hell): Move Abilities to better place
CreatureDestroyAction destroy;
CreatureMoveAction move;
CreatureGatherAction gather;
void Init(Creature* role) {
  wall.SetDestroy(ground);
  portal.AddFoundation(path);
  portal.AddFoundation(ground);
  ground.BindCostSeeThrough(*role, 0);
  path.BindCostSeeThrough(*role, 0);
  wall.BindCostSeeThrough(*role, 0x3f3f3f3f);
  ground.BindCostMove(*role, 0);
  path.BindCostMove(*role, 1);
  wall.BindCostMove(*role, -1);
  role->SetViewDis(6);
  // TODO(handsome0hell): Read block from file
  kMainRenderer->set_exterior_of_building('#', wall);
  kMainRenderer->set_exterior_of_building('.', ground);
  kMainRenderer->set_exterior_of_building('+', path);
  kMainRenderer->set_exterior_of_building('0', portal);
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
  builder.SetEmptyBuilding(empty);
  builder.SetPortalBuilding(portal);
  Space main_space(&builder, {32, 32}, GenerateRandom);
  Creature_ref main_role = Creature::Create();
  Init(main_role.get());
  // TODO(handsome0hell): Read block from file
  std::list<Building> valid;
  valid.push_back(path);
  valid.push_back(ground);
  auto new_map = main_space.NewMap();
  main_role->Teleport(new_map, new_map->PickRandomPointIn(valid));
  AutoResetStatus null_status;
  CinInput_ref input =
      CinInput::CreateCinInput([&null_status](){null_status.set_status();});
  AutoResetStatus quit_status;
  AutoResetStatus render_memory_status;
  input->BindKey('w', [&main_role](){main_role->Perform< 0, -1 >(move);});
  input->BindKey('a', [&main_role](){main_role->Perform< -1, 0 >(move);});
  input->BindKey('s', [&main_role](){main_role->Perform< 0, 1 >(move);});
  input->BindKey('d', [&main_role](){main_role->Perform< 1, 0 >(move);});
  input->BindKey('i', [&main_role](){main_role->Perform< 0, -1 >(destroy);});
  input->BindKey('j', [&main_role](){main_role->Perform< -1, 0 >(destroy);});
  input->BindKey('k', [&main_role](){main_role->Perform< 0, 1 >(destroy);});
  input->BindKey('l', [&main_role](){main_role->Perform< 1, 0 >(destroy);});
  input->BindKey('t', [&main_role](){main_role->Perform< 0, -1 >(gather);});
  input->BindKey('f', [&main_role](){main_role->Perform< -1, 0 >(gather);});
  input->BindKey('g', [&main_role](){main_role->Perform< 0, 1 >(gather);});
  input->BindKey('h', [&main_role](){main_role->Perform< 1, 0 >(gather);});
  input->BindKey('q', [&quit_status](){quit_status.set_status();});
  input->BindKey('m', [&render_memory_status](){
                            render_memory_status.set_status();
                         });
  input->BindKey('n', [main_role](){main_role->Interact();});
  do {
    if (!null_status.Status()) {
      // TODO(handsome0hell): Finish energy system
      main_role->set_now_energy(10);
      main_role->UpdateViewable();
      system("clear");
      if (render_memory_status.Status()) {
        kMainRenderer->RenderMemory(main_role->GetMemory());
      } else {
        kMainRenderer->RenderCreaturesView(*main_role);
      }
      std::cout << std::flush;
    }
    input->HandleInput();
  } while (!quit_status.Status());
}
