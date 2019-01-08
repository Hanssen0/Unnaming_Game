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
#include "Object/LivingThing.h"
#include "Interface/Object.h"
#include "FrontEnd/CinInput.h"
#include "Graphic/Renderer.h"
#include "Map/World.h"
#include "Interface/Random.h"
#include <list>
#include <iostream>
#include <functional>
#include <random>
Renderer_ref kMainRenderer = Renderer::CreateRenderer();
void Init(LivingThing* role) {
  Object::CostOfBlock cost;
  cost.move = 0;
  cost.see_through = 1;
  role -> set_cost(Map::kBlockPath, cost);
  role -> set_cost(Map::kBlockGround, cost);
  cost.move = -1;
  cost.see_through = -1;
  role -> set_cost(Map::kBlockWall, cost);
  role -> set_max_energy(10);
  role -> set_now_energy(10);
  role -> set_view_dis(6);
  kMainRenderer -> set_exterior_of_block(' ', Map::kBlockEmpty);
  kMainRenderer -> set_exterior_of_block('#', Map::kBlockWall);
  kMainRenderer -> set_exterior_of_block('.', Map::kBlockPath);
  kMainRenderer -> set_exterior_of_block('+', Map::kBlockGround);
  //kMainRenderer.set_exterior_of_race('@', kLivingThingsHuman);
}
template <int32_t x, int32_t y>
inline void MoveObj(Object* const obj) {
  Point now_pos = obj -> now_pos();
  now_pos.x += x;
  now_pos.y += y;
  obj -> GoTo(now_pos);
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
class DefaultUIRandom : public UniformIntRandom {
 public:
  inline DefaultUIRandom() {};
  inline void set_seed(const int32_t& seed) override {
    random_engine_.seed(seed);
  }
  inline int32_t rand(const int32_t& from, const int32_t& to) override {
    static std::uniform_int_distribution< int > rand_dis;
    typedef std::uniform_int_distribution< int >::param_type party;
    return rand_dis(random_engine_, party(from, to));
  }

 private:
  std::default_random_engine random_engine_;
};
int main() {
  DefaultUIRandom re;
  re.set_seed(time(0));
  MapBuilder builder(&re, CreateRect(3, 3), CreateRect(8, 8));
  World main_world(&re, &builder, CreateRect(32, 32));
  LivingThing main_role(&main_world);
  Init(&main_role);
  main_role.set_now_map(main_world.NewMap());
  main_role.set_now_pos(main_role.now_map().PickARandomPointInGroundOrPath(re));
  main_world.Arrive(main_role.now_map());
  AutoResetStatus null_status;
  CinInput_ref input =
      CinInput::CreateCinInput(std::bind(&AutoResetStatus::set_status, &null_status));
  AutoResetStatus quit_status;
  AutoResetStatus new_map_status;
  AutoResetStatus render_memory_status;
  input -> BindKey('w', std::bind(MoveObj< 0, -1 >, &main_role));
  input -> BindKey('a', std::bind(MoveObj< -1, 0 >, &main_role));
  input -> BindKey('s', std::bind(MoveObj< 0, 1 >, &main_role));
  input -> BindKey('d', std::bind(MoveObj< 1, 0 >, &main_role));
  input -> BindKey('q', std::bind(&AutoResetStatus::set_status, &quit_status));
  input -> BindKey('m', std::bind(&AutoResetStatus::set_status, &render_memory_status));
  input -> BindKey('n', std::bind(&AutoResetStatus::set_status, &new_map_status));
  bool is_init_stat = true;
  while (!quit_status.Status()) {
    if (is_init_stat) {
      is_init_stat = false;
    } else {
      input -> HandleInput();
    }
    if (!null_status.Status()) {
      if (new_map_status.Status()) {
        Map::Target tmp = main_world.GetTarget(main_role.now_map(), main_role.now_pos());
        main_world.Left(main_role.now_map());
        main_role.set_now_map(tmp.map);
        main_role.set_now_pos(main_role.now_map().PickARandomPointInGroundOrPath(re));
        main_world.Arrive(main_role.now_map());
      }
      main_role.UpdateViewable();
      system("clear");
      if (render_memory_status.Status()) {
        kMainRenderer -> RenderMemory(main_role.GetMemory());
      } else {
        kMainRenderer -> RenderLivingThingsView(main_role);
      }
      std::cout << std::flush;
    }
  }
}
