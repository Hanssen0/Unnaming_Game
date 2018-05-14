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
#include "Map/GameMap.h"
#include "Base.h"
#include "Object/LivingThings.h"
#include "Graphic/Renderer.h"
#include "Map/World.h"
#include <list>
#include <iostream>
RandomGenerater kMainThreadRandom;
LivingThings kMainRole;
Renderer kMainRenderer;
void Init() {
  kMainThreadRandom.set_seed_of_random(time(0));
  kMainRole.set_race(kLivingThingsHuman);
  kMainRole.set_moveable(kBlockEmpty, false);
  kMainRole.set_moveable(kBlockWall, false);
  kMainRole.set_moveable(kBlockPath, true);
  kMainRole.set_moveable(kBlockGround, true);
  kMainRole.set_see_through_able(kBlockEmpty, true);
  kMainRole.set_see_through_able(kBlockWall, false);
  kMainRole.set_see_through_able(kBlockPath, true);
  kMainRole.set_see_through_able(kBlockGround, true);
  kMainRole.set_view_dis(6);
  kMainRenderer.set_exterior_of_block('#', kBlockWall);
  kMainRenderer.set_exterior_of_block('.', kBlockPath);
  kMainRenderer.set_exterior_of_block('+', kBlockGround);
  kMainRenderer.set_exterior_of_race('@', kLivingThingsHuman);
}
int main() {
  Init();
  World main_world;
  GameMapBuilder builder;
  builder.set_random_gen(&kMainThreadRandom);
  main_world.set_builder(&builder);
  main_world.set_random_gen(&kMainThreadRandom);
  GameMap * active_map = main_world.NewMap();
  bool is_new_map = true;
  char com = ' ';
  bool renderer_map = false;
  LivingThings::MemoryOfMap * mem;
  Point now_pos = active_map -> PickARandomPointInGroundOrPath(&kMainThreadRandom);
  GameMap * last_map = nullptr;
  do {
    switch (com) {
     case 'w':
      --now_pos.y;
      break;
     case 'a':
      --now_pos.x;
      break;
     case 's':
      ++now_pos.y;
      break;
     case 'd':
      ++now_pos.x;
      break;
     case 'm':
      renderer_map = true;
      break;
     case ' ':
      if (active_map -> building(kMainRole.now_pos()) == kBuildingPortal) {
        auto tmp = main_world.GetTarget(active_map, kMainRole.now_pos());
        GameMap * tmp_map = tmp -> target_map;
        now_pos = tmp -> target_pos;
        main_world.Left(active_map);
        active_map = tmp_map;
        is_new_map = true;
      }
      break;
     case 'r':
      main_world.Arrive(active_map);
      if (last_map != nullptr) {
        main_world.Left(last_map);
      }
      last_map = active_map;
      break;
     case 'c':
      if (active_map -> building(kMainRole.now_pos()) == kBuildingPortal) {
        GameMap::TargetInMap tmp;
        tmp.target_map = last_map;
        tmp.target_pos = last_map -> PickARandomPointInGroundOrPath(&kMainThreadRandom);
        active_map -> set_portal_target(kMainRole.now_pos(), tmp);
      }
      break;
    }
    if (is_new_map) {
      kMainRole.set_now_map(active_map);
      kMainRole.set_now_pos(now_pos);
      main_world.Arrive(active_map);
      is_new_map = false;
    }
    kMainRole.GoTo(now_pos);
    now_pos = kMainRole.now_pos();
    kMainRole.UpdateViewAble();
    system("clear");
    if (renderer_map) {
      mem = kMainRole.GetMemory();
      kMainRenderer.RenderMemory(*mem);
      renderer_map = false;
    } else {
      kMainRenderer.RenderLivingThingsView(kMainRole);
    }
    std::cout << std::flush;
    main_world.Test();
    com = std::cin.get();
    std::cin.get();
  } while (com != 'q');
}
