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
  for (size_t j = 0; j < obj.now_map().height(); ++j) {
    for (size_t i = 0; i < obj.now_map().width(); ++i) {
      if (i == obj.now_pos().x && j == obj.now_pos().y) {
        std::cout << "@";
      } else if (obj.is_viewable(CreatePoint(i, j))) {
        std::cout << exterior_of_block_[obj.now_map().block(CreatePoint(i, j))];
      } else {
        std::cout << " ";
      }
    }
    std::cout << '\n';
  }
}
void Renderer::RenderGameMap(const Map& map) const {
  for (uint32_t j = 0; j < map.height(); ++j) {
    for (uint32_t i = 0; i < map.width(); ++i) {
      Map::BlockType now_block = map.block(CreatePoint(i, j));
      std::cout << exterior_of_block_[now_block];
    }
    std::cout << "\n";
  }
}
void Renderer::RenderMemory(const Object::MemoryOfMap& mem) const {
  for (uint32_t j = mem.left_top.y; j <= mem.right_bottom.y; ++j) {
    for (uint32_t i = mem.left_top.x; i <= mem.right_bottom.x; ++i) {
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
