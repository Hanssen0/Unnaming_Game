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
#include "ConstValue.h"
#include "CPP.h"
#include "Object/LivingThings.h"
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
  char com;
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
    }
    main_role.GoTo(init_pos);
    init_pos = main_role.now_pos();
    main_role.UpdateViewAble(init_pos);
    system("clear");
    for (int j = 0; j < (main_role.view_dis() << 1) + 1; ++j) {
      for (int i = 0; i < (main_role.view_dis() << 1) + 1; ++i) {
        std::cout << main_role.viewable(TempPoint(i, j));
      }
      std::cout << '\n';
    }
    for (int j = 0; j < kMapHeight; ++j) {
      if (j + main_role.view_dis() < main_role.now_pos().y ||
          j > main_role.now_pos().y + main_role.view_dis()) {
        std::cout << '\n';
        continue;
      }
      for (int i = 0; i < kMapWidth; ++i) {
        if (i + main_role.view_dis() < main_role.now_pos().x) {
          std::cout << ' ';
          continue;
        }
        if (i > main_role.now_pos().x + main_role.view_dis()) {
          break;
        }
        Point tmp;
        tmp.x = main_role.view_dis() - main_role.now_pos().x + i;
        tmp.y = main_role.view_dis() - main_role.now_pos().y + j;
        if (!main_role.viewable(tmp)) {
          std::cout << " ";
          continue;
        }
        if (i == main_role.now_pos().x && j == main_role.now_pos().y) {
          std::cout << "@";
        }else {
          switch (test_map.data(TempPoint(i, j))) {
           case kBlockWall:
            std::cout << "#";
            break;
           case kBlockPath:
            std::cout << ".";
            break;
           case kBlockGround:
            std::cout << "+";
            break;
           default:
            break;
          }
        }
      }
      std::cout << '\n';
    }
    std::cout << std::flush;
  } while ((com = std::cin.get()) != 'q');
}
