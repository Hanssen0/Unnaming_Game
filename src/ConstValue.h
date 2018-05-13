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
#ifndef UNNAMING_GAME_SRC_CONSTVALUE_H_
#define UNNAMING_GAME_SRC_CONSTVALUE_H_
const uint32_t kMapWidth = 32;
const uint32_t kMapHeight = 32;
const uint32_t kMinRoomWidth = 3;
const uint32_t kMinRoomHeight = 3;
const uint32_t kMaxRoomWidth = 8;
const uint32_t kMaxRoomHeight = 8;
enum BlockType {
  kBlockWall,
  kBlockGround,
  kBlockPath,
  kBlockMax
};
#endif  // UNNAMING_GAME_SRC_CONSTVALUE_H_
