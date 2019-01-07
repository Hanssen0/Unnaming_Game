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
#include "Interface/Input.h"
#include "FrontEnd/KeyBoardInput.h"
#include "Graphic/Renderer.h"
#include "Map/World.h"
#include "Interface/Random.h"
#include <list>
#include <iostream>
#include <random>
Renderer& kMainRenderer = *Renderer::CreateRenderer();
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
  kMainRenderer.set_exterior_of_block('#', Map::kBlockWall);
  kMainRenderer.set_exterior_of_block('.', Map::kBlockPath);
  kMainRenderer.set_exterior_of_block('+', Map::kBlockGround);
  //kMainRenderer.set_exterior_of_race('@', kLivingThingsHuman);
}
class CommandForW : public Input::Command {
 public:
  inline void Execute(Object& obj) override {
    Point now_pos = obj.now_pos();
    --now_pos.y;
    obj.GoTo(now_pos);
  }
};
class CommandForA : public Input::Command {
 public:
  inline void Execute(Object& obj) override {
    Point now_pos = obj.now_pos();
    --now_pos.x;
    obj.GoTo(now_pos);
  }
};
class CommandForS : public Input::Command {
 public:
  inline void Execute(Object& obj) override {
    Point now_pos = obj.now_pos();
    ++now_pos.y;
    obj.GoTo(now_pos);
  }
};
class CommandForD : public Input::Command {
 public:
  inline void Execute(Object& obj) override {
    Point now_pos = obj.now_pos();
    ++now_pos.x;
    obj.GoTo(now_pos);
  }
};
class CommandForState : public Input::Command {
 public:
  inline CommandForState() {is_executed_ = false;}
  inline void Execute(Object&) override {
    is_executed_ = true;
  }
  inline bool is_executed() {
    const bool tmp = is_executed_;
    is_executed_ = false;
    return tmp; 
  }

 private:
  bool is_executed_;
};
class DefaultUIRandom : public UniformIntRandom {
 public:
  inline DefaultUIRandom() {};
  inline void set_seed(const int32_t& seed) override {
    random_engine_.seed(seed);
  }
  inline const int32_t rand(const int32_t& from, const int32_t& to) override {
    static std::uniform_int_distribution< int > rand_dis;
    typedef std::uniform_int_distribution< int >::param_type party;
    return rand_dis(random_engine_, party(from, to));
  }

 private:
  std::default_random_engine random_engine_;
};
class CommandForTransfer : public Input::Command {
 public:
  inline void Execute(Object& obj) override {
    obj.Transfer(record_pos_, to_);
  }
  inline void Record(const Point& pos) override {
    record_pos_ = pos;
  }
  inline void Record(const Map::BlockType& t) override {
    to_ = t;
  }

 private:
  Point record_pos_;
  Map::BlockType to_;
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
  CommandForState command_default;
  TerminalKeyBoardInput input(command_default);
  CommandForW command_w;
  CommandForA command_a;
  CommandForS command_s;
  CommandForD command_d;
  CommandForState command_quit;
  CommandForState command_render_memory;
  CommandForState command_new_world;
  input.set_command_for_key('w', &command_w);
  input.set_command_for_key('a', &command_a);
  input.set_command_for_key('s', &command_s);
  input.set_command_for_key('d', &command_d);
  input.set_command_for_key('q', &command_quit);
  input.set_command_for_key('m', &command_render_memory);
  input.set_command_for_key('n', &command_new_world);
  bool is_init_stat = true;
  while (!command_quit.is_executed()) {
    if (is_init_stat) {
      is_init_stat = false;
    } else {
      input.HandleInput().Execute(main_role);
    }
    if (!command_default.is_executed()) {
      if (command_new_world.is_executed()) {
        Map::Target tmp = main_world.GetTarget(main_role.now_map(), main_role.now_pos());
        main_world.Left(main_role.now_map());
        main_role.set_now_map(tmp.map);
        main_role.set_now_pos(main_role.now_map().PickARandomPointInGroundOrPath(re));
        main_world.Arrive(main_role.now_map());
      }
      main_role.UpdateViewable();
      system("clear");
      if (command_render_memory.is_executed()) {
        kMainRenderer.RenderMemory(main_role.GetMemory());
      } else {
        kMainRenderer.RenderLivingThingsView(main_role);
      }
      std::cout << std::flush;
    }
  }
}
