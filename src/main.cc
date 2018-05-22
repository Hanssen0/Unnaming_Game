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
#include <list>
#include <iostream>
#include <random>
LivingThing kMainRole;
Renderer kMainRenderer;
void Init() {
  Object::CostOfBlock cost;
  cost.move = 0;
  kMainRole.set_cost(Map::kBlockPath, cost);
  kMainRole.set_cost(Map::kBlockGround, cost);
  cost.move = -1;
  kMainRole.set_cost(Map::kBlockWall, cost);
  kMainRole.set_max_energy(10);
  kMainRole.set_now_energy(10);
  kMainRenderer.set_exterior_of_block('#', Map::kBlockWall);
  kMainRenderer.set_exterior_of_block('.', Map::kBlockPath);
  kMainRenderer.set_exterior_of_block('+', Map::kBlockGround);
  //kMainRenderer.set_exterior_of_race('@', kLivingThingsHuman);
}
class CommandForW : public Input::Command {
 public:
  void Execute(Object& obj) override {
    Point now_pos = obj.now_pos();
    --now_pos.y;
    obj.GoTo(now_pos);
  }
};
class CommandForA : public Input::Command {
 public:
  void Execute(Object& obj) override {
    Point now_pos = obj.now_pos();
    --now_pos.x;
    obj.GoTo(now_pos);
  }
};
class CommandForS : public Input::Command {
 public:
  void Execute(Object& obj) override {
    Point now_pos = obj.now_pos();
    ++now_pos.y;
    obj.GoTo(now_pos);
  }
};
class CommandForD : public Input::Command {
 public:
  void Execute(Object& obj) override {
    Point now_pos = obj.now_pos();
    ++now_pos.x;
    obj.GoTo(now_pos);
  }
};
class CommandForQ : public Input::Command {
 public:
  CommandForQ() {is_quit_ = false;}
  void Execute(Object& obj) override {
    is_quit_ = true;
  }
  bool is_quit() const {return is_quit_;}

 private:
  bool is_quit_;
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
class NullCommand : public Input::Command {
 public:
  void Execute(Object& obj) override {
  }

};
int main() {
  Init();
  std::default_random_engine re(time(0));
  MapBuilder builder(re);
  World main_world(re, builder);
  Map* active_map = main_world.NewMap();
  kMainRole.set_now_map(*active_map);
  kMainRole.set_now_pos(active_map -> PickARandomPointInGroundOrPath(re));
  NullCommand command_default;
  TerminalKeyBoardInput input(command_default);
  CommandForW command_w;
  CommandForA command_a;
  CommandForS command_s;
  CommandForD command_d;
  CommandForQ command_q;
  input.set_command_for_key('w', command_w);
  input.set_command_for_key('a', command_a);
  input.set_command_for_key('s', command_s);
  input.set_command_for_key('d', command_d);
  input.set_command_for_key('q', command_q);
  do {
    input.HandleInput().Execute(kMainRole);
    kMainRenderer.RenderLivingThingsView(kMainRole);
    std::cout << std::flush;
  } while (!command_q.is_quit());
}
