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
#include "Renderer.h"
#include "../Map/GameMap.h"
void Renderer::RenderLivingThingsView(const LivingThings * thing) {
  uint32_t v_dis = thing -> view_dis();
  for (size_t j = 0; j < thing -> viewable_size(); ++j) {
    for (size_t i = 0; i < thing -> viewable_size(); ++i) {
      Point temp = TempPoint(i, j);
      if (i == v_dis && j == v_dis) {
        std::cout << exterior_of_race_[thing -> race()];
      } else if (thing -> viewable(temp)) {
        std::cout << exterior_of_block_[thing ->
                                            now_map() ->
                                                data(
                                                    TempPoint(
                                                        thing -> now_pos().x
                                                        + i - v_dis,
                                                        thing -> now_pos().y
                                                        + j - v_dis))];
      } else {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
}
void Renderer::RenderGameMap(const GameMap * map) {
  for (uint32_t j = 0; j < kMapHeight; ++j) {
    for (uint32_t i = 0; i < kMapWidth; ++i) {
      std::cout << exterior_of_block_[map -> data(TempPoint(i, j))];
    }
    std::cout << "\n";
  }
}
