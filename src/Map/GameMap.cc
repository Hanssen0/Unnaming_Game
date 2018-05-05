#include "GameMap.h"
void GameMapBuilder::CleanMap(GameMap * game_map) {
  for (int i = 0; i < kMapWidth; ++i) {
    for (int j = 0; j < kMapHeight; ++j) {
      game_map -> data_[i][j] = kBlockEmpty;
    }
  }
  try_to_make.w = kMaxRoomWidth;
  try_to_make.h = kMaxRoomHeight;
}
void GameMapBuilder::UpdateCheckedBuildAble(const Point & pos_to_update) {
  Rect & now = checked_build_able[pos_to_update.x][pos_to_update.y];
  if (pos_to_update.x > 0) {
    now = checked_build_able[pos_to_update.x - 1][pos_to_update.y];
    if (now.w > 0) --now.w;
  }
  if (pos_to_update.x > 0 && pos_to_update.y > 0) {
    now = checked_build_able[pos_to_update.x - 1][pos_to_update.y - 1];
    if (now.w > 0) --now.w;
    if (now.h > 0) --now.h;
  }
  if (pos_to_update.y > 0) {
    now = checked_build_able[pos_to_update.x][pos_to_update.y - 1];
    if (now.h > 0) --now.h;
  }
}
void GameMapBuilder::BuildRooms(GameMap * game_map) {
  InitForEmptyTest();
  while (BuildRoom(game_map));
}
void GameMapBuilder::InitForEmptyTest() {
  for (int i = 0; i < kMapWidth; ++i) {
    for (int j = 0; j < kMapHeight; ++j) {
      checked_build_able[i][j].w = 0;
      checked_build_able[i][j].h = 0;
    }
  }
}
bool GameMapBuilder::SelectRoomPosition(const GameMap * game_map,
                                        RectWithPos * rect_for_build) {
  std::queue< Point > build_able_point;
  for (rect_for_build -> left_top.x = 0;
       rect_for_build -> left_top.x < kMapWidth;
       ++rect_for_build -> left_top.x) {
    for (rect_for_build -> left_top.y = 0;
         rect_for_build -> left_top.y < kMapHeight;
         ++rect_for_build -> left_top.y) {
      if (IsRectEmpty(game_map, *rect_for_build)) {
        build_able_point.push(rect_for_build -> left_top);
      }
    }
  }
  if (build_able_point.size() == 0) return false;
  int select_a_pos = RandomIn(1, build_able_point.size());
  for (int i = 1; i < select_a_pos; ++i) {
    build_able_point.pop();
  }
  rect_for_build -> left_top = build_able_point.front();
  return true;
}
bool GameMapBuilder::BuildRoom(GameMap * game_map) {
  RectWithPos new_room;
  Rect random_rect = RandomRoomRect();
  new_room.w = random_rect.w;
  new_room.h = random_rect.h;
  if (!SelectRoomPosition(game_map, &new_room)) {
    return false;
  }
  for (int i = 0; i < new_room.w; ++i) {
    for (int j = 0; j < new_room.h; ++j) {
      if (i == 0 || j == 0 || i == new_room.w - 1 || j == new_room.h - 1) {
        game_map -> data_[new_room.left_top.x + i][new_room.left_top.y + j] =
            kBlockWall;
      }else {
        game_map -> data_[new_room.left_top.x + i][new_room.left_top.y + j] =
            kBlockGround;
      }
    }
  }
  //Keep the checked array correct
  Point now = new_room.left_top;
  now.x -= kMaxRoomWidth;
  now.y -= kMaxRoomHeight;
  now.x = std::max(0, now.x);
  now.y = std::max(0, now.y);
  for (; now.x < new_room.left_top.x + new_room.w; ++now.x) {
    for (; now.y < new_room.left_top.y + new_room.h; ++now.y) {
      if (now.x >= new_room.left_top.x && now.y >= new_room.left_top.y) {
        checked_build_able[now.x][now.y].w = 0;
        checked_build_able[now.x][now.y].h = 0;
      }else if (now.x < new_room.left_top.x) {
        checked_build_able[now.x][now.y].w =
            std::min(checked_build_able[now.x][now.y].w,
                     new_room.left_top.x - now.x);
      }else {
        checked_build_able[now.x][now.y].h =
            std::min(checked_build_able[now.x][now.y].h,
                     new_room.left_top.y - now.y);
      }
    }
  }
  return true;
}
bool GameMapBuilder::IsRectEmpty(const GameMap * game_map, 
                                 const RectWithPos & rect_for_check) {
  const Point & rect_l_t = rect_for_check.left_top; //Shorter code
  if ((rect_for_check.w + rect_l_t.x > kMapWidth) || 
      (rect_for_check.h + rect_l_t.y > kMapHeight)) return false;
  UpdateCheckedBuildAble(rect_l_t);
  //Shorter code, the result will be saved to the checked array
  Rect & now = checked_build_able[rect_l_t.x][rect_l_t.y];
  //Can I continue to expand the width or height?
  bool is_max_w = false, is_max_h = false;
  //Won't check too much area
  now.w = std::min(now.w, rect_for_check.w);
  now.h = std::min(now.h, rect_for_check.h);
  while (!(now.w == rect_for_check.w || is_max_w) || 
         !(now.h == rect_for_check.h || is_max_h)) {
    //Try to expand width
    if (!is_max_w && now.w != rect_for_check.w) {
      for (int i = 0; i < now.h; ++i) {
        if (game_map -> data_[rect_l_t.x + now.w][rect_l_t.y + i] !=
            kBlockEmpty &&
            game_map -> data_[rect_l_t.x + now.w][rect_l_t.y + i] !=
            kBlockWall) {
          is_max_w = true; //Oops, can't expand anymore
          --now.w; //Keep width
          break;
        }
      }
      ++now.w;
    } 
    //Try to expand height 
    if (!is_max_h && now.h != rect_for_check.h) {
      for (int i = 0; i < now.w; ++i) {
        if (game_map -> data_[rect_l_t.x + i][rect_l_t.y + now.h] !=
            kBlockEmpty &&
            game_map -> data_[rect_l_t.x + i][rect_l_t.y + now.h] !=
            kBlockWall) {
          is_max_h = true; //Oops, can't expand anymore
          --now.h; //Keep height
          break;
        }
      }
      ++now.h;
    } 
  }
  if (now.w == rect_for_check.w && now.h == rect_for_check.h) {
    return true;
  }else {
    return false;
  }
}
