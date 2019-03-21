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
#include "Map/Map.h"
#include "Logic/MapBuilder.h"
#include "Object/Creature.h"
#include "FrontEnd/CinInput.h"
#include "Graphic/Renderer.h"
#include "Map/World.h"
#include <list>
#include <iostream>
#include <functional>
#include <random>
Renderer_ref kMainRenderer = Renderer::Create();
void Init(Creature* role) {
  Creature::CostOfBlock_ref normal_cost = Creature::CostOfBlock::Create();
  Creature::CostOfBlock_ref stop_cost = Creature::CostOfBlock::Create();
  // TODO: Read block from file
  role -> UpdateBlockTypeSize(4);
  normal_cost -> BindMoveCost([]() -> int32_t {return 1;});
  normal_cost -> BindSeeThroughCost([]() -> int32_t {return 1;});
  role -> set_cost(2, normal_cost);
  role -> set_cost(3, normal_cost);
  stop_cost -> BindMoveCost([]() -> int32_t {return -1;});
  stop_cost -> BindSeeThroughCost([]() -> int32_t {return -1;});
  role -> set_cost(1, stop_cost);
  role -> set_max_energy(10);
  role -> set_now_energy(10);
  role -> set_view_dis(6);
  // TODO: Read block from file
  kMainRenderer -> UpdateBlockTypeSize(4);
  kMainRenderer -> set_exterior_of_block(' ', 0);
  kMainRenderer -> set_exterior_of_block('#', 1);
  kMainRenderer -> set_exterior_of_block('.', 2);
  kMainRenderer -> set_exterior_of_block('+', 3);
}
class AutoResetStatus {
 public:
  inline AutoResetStatus() : status_(false) {};
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
  std::uniform_int_distribution< int > rand_dis;
  random_engine.seed(time(0));
  std::function< int32_t(int32_t, int32_t) > GenerateRandom = 
      [&random_engine, &rand_dis](int32_t from, int32_t to) -> int32_t {
        return rand_dis(random_engine,
                        std::uniform_int_distribution< int >::param_type(from,
                                                                         to)
                       );
      };
  MapBuilder builder(GenerateRandom, {3, 3}, {8, 8});
  World main_world(GenerateRandom, &builder, {32, 32});
  Creature_ref main_role = Creature::CreateCreature(&main_world);
  Init(main_role.get());
  main_role -> set_now_map(main_world.NewMap());
  // TODO: Read block from file
  std::list< Map::BlockType > valid;
  valid.push_back(2);
  valid.push_back(3);
  main_role -> set_now_position(
                   main_role -> now_map()
                       -> PickARandomPointInGroundOrPath(GenerateRandom, valid));
  main_world.Arrive(main_role -> now_map());
  AutoResetStatus null_status;
  CinInput_ref input =
      CinInput::CreateCinInput([&null_status](){null_status.set_status();});
  AutoResetStatus quit_status;
  AutoResetStatus new_map_status;
  AutoResetStatus render_memory_status;
  input -> BindKey('w', [&main_role](){main_role -> Move< 0, -1 >();});
  input -> BindKey('a', [&main_role](){main_role -> Move< -1, 0 >();});
  input -> BindKey('s', [&main_role](){main_role -> Move< 0, 1 >();});
  input -> BindKey('d', [&main_role](){main_role -> Move< 1, 0 >();});
  input -> BindKey('q', [&quit_status](){quit_status.set_status();});
  input -> BindKey('m', [&render_memory_status](){
                            render_memory_status.set_status();
                         });
  input -> BindKey('n', [&new_map_status](){new_map_status.set_status();});
  bool is_init_stat = true;
  while (!quit_status.Status()) {
    if (is_init_stat) {
      is_init_stat = false;
    } else {
      input -> HandleInput();
    }
    if (!null_status.Status()) {
      // TODO: Finish energy system
      main_role -> set_now_energy(10);
      if (new_map_status.Status()) {
        Map::Target tmp = main_world.GetTarget(main_role -> now_map(),
                                               main_role -> now_position());
        main_world.Left(main_role -> now_map());
        main_role -> set_now_map(tmp.map);
        // TODO: Read block from file
        main_role -> set_now_position(
                         main_role -> now_map()
                             -> PickARandomPointInGroundOrPath(GenerateRandom, valid));
        main_world.Arrive(main_role -> now_map());
      }
      main_role -> UpdateViewable();
      system("clear");
      if (render_memory_status.Status()) {
        kMainRenderer -> RenderMemory(main_role -> GetMemory());
      } else {
        kMainRenderer -> RenderCreaturesView(*main_role);
      }
      std::cout << std::flush;
    }
  }
}
