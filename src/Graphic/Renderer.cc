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
void Renderer::RenderLivingThingsView(const LivingThings & thing) const {
  for (size_t j = 0; j < thing.viewable_size(); ++j) {
    for (size_t i = 0; i < thing.viewable_size(); ++i) {
      Point temp = TempPoint(i, j);
      if (i == thing.view_dis() && j == thing.view_dis()) {
        std::cout << exterior_of_race_[thing.race()];
      } else if (thing.viewable(temp)) {
        Point read_point;
        thing.ViewPosToRealPos(TempPoint(i, j), &read_point);
        BlockType now_block = thing.now_map() -> data(read_point);
        std::cout << exterior_of_block_[now_block];
      } else {
        std::cout << ' ';
      }
    }
    std::cout << '\n';
  }
}
void Renderer::RenderGameMap(const GameMap & map) const {
  for (uint32_t j = 0; j < kMapHeight; ++j) {
    for (uint32_t i = 0; i < kMapWidth; ++i) {
      BlockType now_block = map.data(TempPoint(i, j));
      std::cout << exterior_of_block_[now_block];
    }
    std::cout << "\n";
  }
}
void Renderer::RenderMemory(const LivingThings::MemoryOfMap & mem) const {
  for (uint32_t j = mem.left_top.y; j <= mem.right_bottom.y; ++j) {
    for (uint32_t i = mem.left_top.x; i <= mem.right_bottom.x; ++i) {
      if (mem.is_seen[i][j]) {
        BlockType now_block = mem.detail.data(TempPoint(i, j));
        std::cout << exterior_of_block_[now_block];
      } else {
        std::cout << ' ';
      }
    }
    std::cout << "\n";
  }
}
