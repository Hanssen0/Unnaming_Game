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
#include <iostream>
int main() {
  RandomGenerater main_random;
  main_random.set_seed_of_random(time(0));
  GameMap test_map;
  GameMapBuilder builder;
  builder.set_random_gen(&main_random);
  builder.set_target_map(&test_map);
  builder.CleanMap();
  builder.BuildRoomsAndPath();
  LivingThings main_role;
  main_role.set_now_map(&test_map);
  main_role.set_race(kLivingThingsHuman);
  main_role.set_moveable(kBlockWall, false);
  main_role.set_moveable(kBlockPath, true);
  main_role.set_moveable(kBlockGround, true);
  main_role.set_see_through_able(kBlockWall, false);
  main_role.set_see_through_able(kBlockPath, true);
  main_role.set_see_through_able(kBlockGround, true);
  main_role.set_view_dis(6);
  Point init_pos;
  bool init_able = false;
  for (uint32_t i = 0; i < kMapWidth; ++i) {
    for (uint32_t j = 0; j < kMapHeight; ++j) {
      if (!init_able && test_map.data(TempPoint(i, j)) == kBlockGround) {
        init_pos.x = i;
        init_pos.y = j;
        init_able = true;
        break;
      }
    }
    if (init_able) break;
  }
  main_role.set_now_pos(init_pos);
  main_role.UpdateViewAble(init_pos);
  char com = ' ';
  Renderer main_renderer;
  main_renderer.set_exterior_of_block('#', kBlockWall);
  main_renderer.set_exterior_of_block('.', kBlockPath);
  main_renderer.set_exterior_of_block('+', kBlockGround);
  main_renderer.set_exterior_of_race('@', kLivingThingsHuman);
  bool renderer_map = false;
  LivingThings::MemoryOfMap * mem;
  do {
    switch (com) {
     case 'w':
      --init_pos.y;
      break;
     case 'a':
      --init_pos.x;
      break;
     case 's':
      ++init_pos.y;
      break;
     case 'd':
      ++init_pos.x;
      break;
     case 'm':
      renderer_map = true;
      break;
    }
    main_role.GoTo(init_pos);
    init_pos = main_role.now_pos();
    main_role.UpdateViewAble(init_pos);
    system("clear");
    if (renderer_map) {
      mem = main_role.GetMemory();
      main_renderer.RenderMemory(*mem);
      renderer_map = false;
    } else {
      main_renderer.RenderLivingThingsView(main_role);
    }
    std::cout << std::flush;
    com = std::cin.get();
    std::cin.get();
  } while (com != 'q');
}
