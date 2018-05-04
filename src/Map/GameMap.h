#ifndef UNNAMING_MAP_GAMEMAP_H_
#define UNNAMING_MAP_GAMEMAP_H_
#include "../CPP.h"
#include "../ConstValue.h"
struct Point {
  int x, y;
};
struct Rect {
  int w, h;
};
struct RectWithPos {
  Point left_top;
  int w, h;
};
class GameMap {
 public:
  inline int data(const int _x,const int _y) const {return data_[_x][_y];}
  inline int set_data(const int _x,const int _y,const int _v) {data_[_x][_y] = _v;}
  friend class GameMapBuilder;
 private:
  int data_[kMapWidth][kMapHeight];
};
class GameMapBuilder {
 public:
  inline void CleanMap(GameMap * game_map);
  inline void BuildRooms(const int room_nums, GameMap * game_map);
 private:
  void BuildRoom(GameMap * game_map);
  void InitForEmptyTest(const GameMap * game_map);
  bool IsRectEmpty(const GameMap * game_map, const RectWithPos & rect_for_check);
  Rect GetEmptyRect(const GameMap * game_map, const Rect & rect_for_check);
  Rect GetEmptyRectWithoutRect(const GameMap * game_map, const RectWithPos & rect_for_check, const Rect & rect_minus);
  inline Rect MaxAreaRect(const Rect &, const Rect &);
  inline Rect RandomRoomRect();
  //for speed up empty test
  Rect checked_build_able[kMapWidth][kMapHeight];
  std::queue< Point > not_link_door;
};
inline Rect GameMapBuilder::RandomRoomRect() {
  Rect ret;
  ret.w = random_in(kMinRoomWidth, kMaxRoomWidth);
  ret.h = random_in(kMinRoomHeight, kMaxRoomHeight);
}
inline Rect GameMapBuilder::MaxAreaRect(const Rect & a, const Rect & b) {
  if (a.w < 0 || a.h < 0) return b;
  if (b.w < 0 || b.h < 0) return a;
  long long a_area = a.w;
  a_area *= a.h;
  long long b_area = b.w;
  b_area *= b.h;
  if (a_area > b_area) {
    return a;
  }else {
    return b;
  }
}
#endif
