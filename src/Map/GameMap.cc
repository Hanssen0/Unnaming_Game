#include "GameMap.h"
void GameMapBuilder::CleanMap(const GameMap * game_map) {
  for (int i = 0; i < kMapWidth; ++i) {
    for (int j = 0; j < kMapHeight; ++j) {
      game_map -> data_[i][j] = kBlockEmpty;
    }
  }
}
void GameMapBuilder::BuildRooms(const int room_nums, GameMap * game_map) {
  InitForEmptyTest(game_map);
  for (int i = 0; i < room_nums; ++i) {
    BuildRoom(game_map);
  }
}
void GameMapBuilder::BuildRoom(GameMap * game_map) {
  RectWithPos new_room;
  Rect random_rect = RandomRoomRect();
  new_room.w = random_rect.w;
  new_room.h = random_rect.h;
  std::queue< Point > build_able_point;
  for (new_room.left_top.x = 0; new_room.left_top.x < kMapWidth;
       ++new_room.left_top.x) {
    for (new_room.left_top.y = 0; new_room.left_top.y < kMapHeight;
         ++new_room.left_top.y) {
      if (IsRectEmpty(game_map, new_room)) {
        build_able_point.push(new_room.left_top);
      }
    }
  }
}
void GameMapBuilder::InitForEmptyTest(const GameMap * game_map) {
  for (int i = 0; i < kMapWidth; ++i) {
    for (int j = 0; j < kMapHeight; ++j) {
      checked_build_able[i][j].w = 0;
      checked_build_able[i][j].h = 0;
    }
  }
}
bool GameMapBuilder::IsRectEmpty(const GameMap * game_map, 
                                 const RectWithPos & rect_for_check) {
  if (rect_for_check.w + rect_for_check.left_top.x > kMapWidth) return false;
  if (rect_for_check.h + rect_for_check.left_top.y > kMapHeight) return false;
  Point rect_l_t = rect_for_check.left_top;
  Rect & now = checked_build_able[rect_l_t.x][rect_l_t.y];
  if (rect_l_t.x > 0) {
    Rect tmp = checked_build_able[rect_l_t.x - 1][rect_l_t.y];
    --tmp.w;
    now = MaxAreaRect(now, tmp);
  }
  if (rect_l_t.y > 0) {
    Rect tmp = checked_build_able[rect_l_t.x][rect_l_t.y - 1];
    --tmp.h;
    now = MaxAreaRect(now, tmp);
  }
  bool is_empty = true;
  Rect max_build_able;
  return true;
}
Rect GameMapBuilder::GetEmptyRect(const GameMap * game_map, const RectWithPos & rect_for_check) {
  Rect ret = {0, 0}; 
  bool is_max_w = false, is_max_h = false;
  while ((ret.w != rect_for_check.w && is_max_w == false) ||
         (ret.h != rect_for_check.h && is_max_h == false)) {
    if (!is_max_w) {
      for (int i = 0; i < ret.h; ++i) {
        if (game_map -> data_[rect_for_check.x + ret.w][rect_for_check.y + i] != kBlockEmpty) {
          is_max_w = true;
          break;
        }
      }
      if (!is_max_w) {
        ++ret.w;
      }
    }
    if (!is_max_h) {
      for (int i = 0; i < ret.w; ++i) {
        if (game_map -> data_[rect_for_check.x + i][rect_for_check.y + ret.h] != kBlockEmpty) {
          is_max_h = true;
          break;
        }
      }
      if (!is_max_h) {
        ++ret.h;
      }
    }
  }
  return ret;
}
Rect GameMapBuilder::GetEmptyRectWithoutRect(const GameMap * game_map,
                                             const RectWithPos & rect_for_check,
                                             const Rect & rect_minus) {
  Rect build_able_area;
  RectWithPos part_of_rect;
  part_of_rect.x = rect_for_check.left_top.x + rect_minus.w;
  part_of_rect.y = rect_for_check.left_top.y;
  part_of_rect.w = rect_for_check.w - rect_minus.w;
  part_of_rect.h = rect_for_check.h;
  if (part_of_rect.w > 0) {
    build_able_area = IsRectEmptyWithSimpleWay(game_map, part_of_rect);
    if ((build_able_area.w < part_of_rect.w) ||
        (build_able_area.h < part_of_rect.h)) {
      build_able_area.w += rect_minus.w;
      return build_able_area;
    }
  }
  part_of_rect.x -= rect_minus.w;
  part_of_rect.y += rect_minus.h;
  part_of_rect.w += rect_minus.w;
  part_of_rect.h -= rect_minus.h;
  if (part_of_rect.h > 0) {
    build_able_area = IsRectEmptyWithSimpleWay(game_map, part_of_rect);
    if ((build_able_area.w < part_of_rect.w) ||
        (build_able_area.h < part_of_rect.h)) {
      build_able_area.h += rect_minus.h;
      return build_able_area;
    }
  }
  part_of_rect.x += rect_minus.w;
  part_of_rect.w -= rect_minus.w;
  if (part_of_rect.h > 0 && part_of_rect.w > 0) {
    build_able_area = IsRectEmptyWithSimpleWay(game_map, part_of_rect);
    if ((build_able_area.w < part_of_rect.w) ||
        (build_able_area.h < part_of_rect.h)) {
      build_able_area.w += rect_minus.w;
      build_able_area.h += rect_minus.h;
      return build_able_area;
    }
  }
  return rect_for_check;
}
