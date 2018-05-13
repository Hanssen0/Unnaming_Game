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
#include "GameMap.h"
void GameMapBuilder::CleanMap() {
  for (uint32_t i = 0; i < kMapWidth; ++i) {
    for (uint32_t j = 0; j < kMapHeight; ++j) {
      target_map_ -> data_[i][j] = kBlockWall;
    }
  }
}
void GameMapBuilder::BuildRoomsAndPath() {
  InitForEmptyTest();
  Point previous;
  bool is_first = true;
  while (true) {
    Point tmp;
    if (!BuildRoom(&tmp)) break;
    if (!is_first) {
      BuildPath(previous, tmp);
    } else {
      is_first = false;
    }
    previous = tmp;
  }
}
void GameMapBuilder::InitForEmptyTest() {
  for (uint32_t i = 0; i < kMapWidth; ++i) {
    for (uint32_t j = 0; j < kMapHeight; ++j) {
      checked_build_able_[i][j].w = 0;
      checked_build_able_[i][j].h = 0;
    }
  }
}
void GameMapBuilder::UpdateCheckedBuildAble(const Point & pos_to_update) {
  Rect & now = checked_build_able_[pos_to_update.x][pos_to_update.y];
  if (pos_to_update.x > 0) {
    now = checked_build_able_[pos_to_update.x - 1][pos_to_update.y];
    if (now.w > 0) --now.w;
  }
  if (pos_to_update.x > 0 && pos_to_update.y > 0) {
    now = checked_build_able_[pos_to_update.x - 1][pos_to_update.y - 1];
    if (now.w > 0) --now.w;
    if (now.h > 0) --now.h;
  }
  if (pos_to_update.y > 0) {
    now = checked_build_able_[pos_to_update.x][pos_to_update.y - 1];
    if (now.h > 0) --now.h;
  }
}
void GameMapBuilder::BuildPath(const Point & from, const Point & to) {
  PathFinder path_designer;
  path_designer.set_value(kBlockWall, 10);
  path_designer.set_value(kBlockGround, 1);
  path_designer.set_value(kBlockPath, 3);
  path_designer.set_target_map(target_map_);
  std::list< Point > shortest_path =
      path_designer.FindShortestPath(from, to);
  std::list< Point >::iterator path_builder = shortest_path.begin();
  while (path_builder != shortest_path.end()) {
    if (target_map_ -> data_[(*path_builder).x][(*path_builder).y] == kBlockWall) {
      target_map_ -> data_[(*path_builder).x][(*path_builder).y] = kBlockPath;
    }
    ++path_builder;
  }
}
bool GameMapBuilder::SelectRoomPosition(RectWithPos * rect_for_build) {
  std::queue< Point > build_able_point;
  for (rect_for_build -> left_top.x = 0;
       rect_for_build -> left_top.x < kMapWidth;
       ++rect_for_build -> left_top.x) {
    for (rect_for_build -> left_top.y = 0;
         rect_for_build -> left_top.y < kMapHeight;
         ++rect_for_build -> left_top.y) {
      if (IsRectEmpty(*rect_for_build)) {
        build_able_point.push(rect_for_build -> left_top);
      }
    }
  }
  if (build_able_point.size() == 0) return false;
  size_t select_a_pos = random_gen_ -> RandomIn(1, build_able_point.size());
  for (size_t i = 1; i < select_a_pos; ++i) {
    build_able_point.pop();
  }
  rect_for_build -> left_top = build_able_point.front();
  return true;
}
bool GameMapBuilder::BuildRoom(Point * room_pos) {
  RectWithPos new_room;
  Rect random_rect = RandomRoomRect();
  new_room.w = random_rect.w;
  new_room.h = random_rect.h;
  if (!SelectRoomPosition(&new_room)) {
    return false;
  }
  for (uint32_t i = 0; i < new_room.w; ++i) {
    for (uint32_t j = 0; j < new_room.h; ++j) {
      // Won't cause room adhesion
      if (!(i == 0 || j == 0 || i + 1 == new_room.w || j + 1 == new_room.h)) {
        target_map_ -> data_[new_room.left_top.x + i][new_room.left_top.y + j] =
            kBlockGround;
      }
    }
  }
  // Keep the checked array correct
  Point now = new_room.left_top;
  now.x -= kMaxRoomWidth;
  now.y -= kMaxRoomHeight;
  now.x = std::max(static_cast< uint32_t >(0), now.x);
  now.y = std::max(static_cast< uint32_t >(0), now.y);
  for (; now.x < new_room.left_top.x + new_room.w; ++now.x) {
    for (; now.y < new_room.left_top.y + new_room.h; ++now.y) {
      if (now.x >= new_room.left_top.x && now.y >= new_room.left_top.y) {
        checked_build_able_[now.x][now.y].w = 0;
        checked_build_able_[now.x][now.y].h = 0;
      } else if (now.x < new_room.left_top.x) {
        checked_build_able_[now.x][now.y].w =
            std::min(checked_build_able_[now.x][now.y].w,
                     new_room.left_top.x - now.x);
      } else {
        checked_build_able_[now.x][now.y].h =
            std::min(checked_build_able_[now.x][now.y].h,
                     new_room.left_top.y - now.y);
      }
    }
  }
  ++new_room.left_top.x;
  ++new_room.left_top.y;
  *room_pos = new_room.left_top;
  return true;
}
bool GameMapBuilder::IsRectEmpty(const RectWithPos & rect_for_check) {
  const Point & rect_l_t = rect_for_check.left_top;  // Shorter code
  if ((rect_for_check.w + rect_l_t.x > kMapWidth) ||
      (rect_for_check.h + rect_l_t.y > kMapHeight)) return false;
  UpdateCheckedBuildAble(rect_l_t);
  // Shorter code, the result will be saved to the checked array
  Rect & now = checked_build_able_[rect_l_t.x][rect_l_t.y];
  // Can I continue to expand the width or height?
  bool is_max_w = false, is_max_h = false;
  // Won't check too much area
  now.w = std::min(now.w, rect_for_check.w);
  now.h = std::min(now.h, rect_for_check.h);
  while (!(now.w == rect_for_check.w || is_max_w) ||
         !(now.h == rect_for_check.h || is_max_h)) {
    // Try to expand width
    if (!is_max_w && now.w != rect_for_check.w) {
      for (uint32_t i = 0; i < now.h; ++i) {
        if (target_map_ -> data_[rect_l_t.x + now.w][rect_l_t.y + i] !=
            kBlockWall &&
            target_map_ -> data_[rect_l_t.x + now.w][rect_l_t.y + i] !=
            kBlockPath) {
          is_max_w = true;  // Oops, can't expand anymore
          --now.w;  // Keep width
          break;
        }
      }
      ++now.w;
    }
    // Try to expand height
    if (!is_max_h && now.h != rect_for_check.h) {
      for (uint32_t i = 0; i < now.w; ++i) {
        if (target_map_ -> data_[rect_l_t.x + i][rect_l_t.y + now.h] !=
            kBlockWall &&
            target_map_ -> data_[rect_l_t.x + i][rect_l_t.y + now.h] !=
            kBlockPath) {
          is_max_h = true;  // Oops, can't expand anymore
          --now.h;  // Keep height
          break;
        }
      }
      ++now.h;
    }
  }
  if (now.w == rect_for_check.w && now.h == rect_for_check.h) {
    return true;
  } else {
    return false;
  }
}
Point evaulate_to;
inline uint32_t EvaulateValue(const Point & po) {
  uint32_t ret = abs(po.x - evaulate_to.x) + abs(po.y - evaulate_to.y);
  return ret;
}
std::list< Point > PathFinder::FindShortestPath(const Point & from,
                                                const Point & to) {
  for (uint32_t i = 0; i < kMapWidth; ++i) {
    for (uint32_t j = 0; j < kMapHeight; ++j) {
      walked_dis_[i][j] = -1;
    }
  }
  for (uint32_t i = 0; i < kMapWidth; ++i) {
    for (uint32_t j = 0; j < kMapHeight; ++j) {
      walked_[i][j] = false;
    }
  }
  evaulate_to = to;
  walked_dis_[from.x][from.y] = value_[target_map_ -> data_[from.x][from.y]];;
  father[from.x][from.y].x = -1;
  searching_list.push_back(from);
  Point min_dis;
  while (!searching_list.empty()) {
    min_dis = searching_list.front();
    searching_list.pop_front();
    if (min_dis.x == to.x && min_dis.y == to.y) {
      break;
    }
    UpdateNearby(min_dis);
  }
  std::list< Point > shortest_path;
  Point backer;
  if (min_dis.x == to.x && min_dis.y == to.y) {
    backer = to;
    while (backer.x != -1) {
      shortest_path.push_front(backer);
      backer = father[backer.x][backer.y];
    }
  }
  return shortest_path;
}
void PathFinder::UpdateNearby(const Point & now) {
  walked_[now.x][now.y] = true;
  Point tmp = now;
  if (tmp.x > 0) {
    --tmp.x;
    if (TryAPoint(target_map_ -> data_[tmp.x][tmp.y],
                  walked_dis_[now.x][now.y] +
                  (father[now.x][now.y].x - 1 == now.x ? 0 : 1),
                  tmp)) {
      father[tmp.x][tmp.y] = now;
    }
    ++tmp.x;
  }
  if (tmp.y > 0) {
    --tmp.y;
    if (TryAPoint(target_map_ -> data_[tmp.x][tmp.y],
                  walked_dis_[now.x][now.y] +
                  (father[now.x][now.y].y - 1 == now.y ? 0 : 1),
                  tmp)) {
      father[tmp.x][tmp.y] = now;
    }
    ++tmp.y;
  }
  if (tmp.x < kMapWidth - 1) {
    ++tmp.x;
    if (TryAPoint(target_map_ -> data_[tmp.x][tmp.y],
                  walked_dis_[now.x][now.y] +
                  (father[now.x][now.y].x + 1 == now.x ? 0 : 1),
                  tmp)) {
      father[tmp.x][tmp.y] = now;
    }
    --tmp.x;
  }
  if (tmp.y < kMapHeight - 1) {
    ++tmp.y;
    if (TryAPoint(target_map_ -> data_[tmp.x][tmp.y],
                  walked_dis_[now.x][now.y] +
                  (father[now.x][now.y].y + 1 == now.y ? 0 : 1),
                  tmp)) {
      father[tmp.x][tmp.y] = now;
    }
    --tmp.y;
  }
}
inline bool operator==(const Point & a, const Point & b) {
  return a.x == b.x && a.y == b.y;
}
bool PathFinder::TryAPoint(const BlockType type, uint32_t walked_dis,
                           const Point & now) {
  if (!walked_[now.x][now.y] && value_[type] >= 0) {
    if (walked_dis_[now.x][now.y] == -1) {
      walked_dis_[now.x][now.y] = walked_dis + value_[type];
      PushPointToAstarList(now);
      return true;
    }
    if (walked_dis_[now.x][now.y] > walked_dis + value_[type]) {
      walked_dis_[now.x][now.y] = walked_dis + value_[type];
      searching_list.erase(std::find(searching_list.begin(),
                                     searching_list.end(),
                                     now));
      PushPointToAstarList(now);
      return true;
    }
  }
  return false;
}
void PathFinder::PushPointToAstarList(const Point & po) {
  std::list< Point >::iterator now = searching_list.begin();
  while (now != searching_list.end() &&
         walked_dis_[(*now).x][(*now).y] + EvaulateValue(*now) <
         walked_dis_[po.x][po.y] + EvaulateValue(po)) {
    ++now;
  }
  searching_list.insert(now, po);
}
