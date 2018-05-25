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
void Renderer::RenderLivingThingsView(const Object& obj) const {
  for (int32_t j = 0; j < ((obj.view_dis() << 1) | 1); ++j) {
    for (int32_t i = 0; i < ((obj.view_dis() << 1) | 1); ++i) {
      const Point tmp = {obj.now_pos().x - obj.view_dis() +
                         static_cast< int32_t >(i), 
                         obj.now_pos().y - obj.view_dis() + 
                         static_cast< int32_t >(j)}; 
      if (tmp == obj.now_pos()) {
        std::cout << "@";
      } else if (obj.is_viewable(tmp)) {
        std::cout << exterior_of_block_[obj.now_map().block(tmp)];
      } else {
        std::cout << " ";
      }
    }
    std::cout << '\n';
  }
}
void Renderer::RenderGameMap(const Map& map) const {
  for (int32_t j = 0; j < map.height(); ++j) {
    for (int32_t i = 0; i < map.width(); ++i) {
      Map::BlockType now_block = map.block(CreatePoint(i, j));
      std::cout << exterior_of_block_[now_block];
    }
    std::cout << "\n";
  }
}
void Renderer::RenderMemory(const Object::MemoryOfMap& mem) const {
  for (int32_t j = mem.left_top.y; j <= mem.right_bottom.y; ++j) {
    for (int32_t i = mem.left_top.x; i <= mem.right_bottom.x; ++i) {
      if (mem.is_seen[i][j]) {
        Map::BlockType now_block = mem.detail.block(CreatePoint(i, j));
        std::cout << exterior_of_block_[now_block];
      } else {
        std::cout << ' ';
      }
    }
    std::cout << "\n";
  }
}
