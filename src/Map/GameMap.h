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
  void PrintMap() {
    for (int j = 0; j < kMapHeight; ++j) {
      for (int i = 0; i < kMapWidth; ++i) {
        switch (data_[i][j]) {
         case kBlockWall:
          std::cout << " ";
          break;
         case kBlockGround:
          std::cout << "0";
          break;
        }
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
  friend class GameMapBuilder;
 private:
  int data_[kMapWidth][kMapHeight];
};
class GameMapBuilder {
 public:
  //Delete everything
  void CleanMap(GameMap * game_map);
  //Make rooms
  void BuildRooms(GameMap * game_map);
 private:
  //Init to speed up empty test
  void InitForEmptyTest();
  //Update array to speed up empty test
  void UpdateCheckedBuildAble(const Point & pos_to_update);
  bool SelectRoomPosition(const GameMap *, RectWithPos *);
  //Build one room
  bool BuildRoom(GameMap * game_map);
  bool IsRectEmpty(const GameMap * game_map, const RectWithPos & rect_for_check);
  inline Rect RandomRoomRect();
  //To speed up empty test
  Rect checked_build_able[kMapWidth][kMapHeight];
  inline const Rect & max(const Rect &, const Rect &);
  //Biggest room to try
  Rect try_to_make;
};
inline Rect GameMapBuilder::RandomRoomRect() {
  Rect ret;
  //Need some space to prevent room adhesion
  ret.w = RandomIn(kMinRoomWidth + 2, kMaxRoomWidth + 2);
  ret.h = RandomIn(kMinRoomHeight + 2, kMaxRoomHeight + 2);
  return ret;
}
inline const Rect & GameMapBuilder::max(const Rect & a, const Rect & b) {
  if (a.w < 0 || a.h < 0) return b;
  if (b.w < 0 || b.h < 0) return a;
  long long a_area = a.w, b_area = b.w;
  a_area *= a.h, b_area *= b.h;
  if (a_area > b_area) {
    return a;
  }else {
    return b;
  }
}
#endif
