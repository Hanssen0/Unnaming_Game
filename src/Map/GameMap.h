#ifndef SRC_MAP_GAMEMAP_H_
#define SRC_MAP_GAMEMAP_H_
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
  inline BlockType data(const int _x,
                        const int _y) const {return data_[_x][_y];}
  inline BlockType set_data(const int _x,
                            const int _y, const BlockType _v) {
    data_[_x][_y] = _v;
  }
  void PrintMap() const {
    for (int j = 0; j < kMapHeight; ++j) {
      for (int i = 0; i < kMapWidth; ++i) {
        switch (data_[i][j]) {
         case kBlockWall:
          std::cout << " ";
          break;
         case kBlockGround:
          std::cout << "0";
          break;
         case kBlockPath:
          std::cout << ".";
          break;
        }
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }
  friend class GameMapBuilder;
  friend class PathFinder;
 private:
  BlockType data_[kMapWidth][kMapHeight];
};
class GameMapBuilder {
 public:
  GameMapBuilder() {random_gen_ = nullptr;}
  // Delete everything
  void CleanMap(GameMap * game_map);
  // Make rooms
  void BuildRoomsAndPath(GameMap * game_map);
  void set_random_gen(RandomGenerater * r) {random_gen_ = r;}
 private:
  // Init to speed up empty test
  void InitForEmptyTest();
  // Update array to speed up empty test
  void UpdateCheckedBuildAble(const Point & pos_to_update);
  // Build path by A*
  void BuildPath(GameMap * game_map, const Point & from, const Point & to);
  bool SelectRoomPosition(const GameMap *, RectWithPos *);
  // Build one room
  Point BuildRoom(GameMap * game_map);
  bool IsRectEmpty(const GameMap * game_map,
                   const RectWithPos & rect_for_check);
  inline Rect RandomRoomRect();
  inline const Rect & max(const Rect &, const Rect &);
  // To speed up empty test
  Rect checked_build_able_[kMapWidth][kMapHeight];
  RandomGenerater * random_gen_;
};
class PathFinder {
 public:
  std::list< Point > FindShortestPath(const GameMap * game_map,
                                      const Point & from, const Point & to);
  inline void set_value(BlockType type, int value) {
    value_[type] = value;
  }

 private:
  struct AstarStat {
    Point self;
    PathFinder * original_finder;
  };
  void UpdateNearby(const GameMap * game_map, const Point & now);
  bool TryAPoint(const BlockType type, int walked_dis, const Point & now);
  void PushPointToAstarList(const Point &);
  int value_[kBlockMax];
  // A star data
  bool walked_[kMapWidth][kMapHeight];
  int walked_dis_[kMapWidth][kMapHeight];
  Point father[kMapWidth][kMapHeight];
  std::list< Point > searching_list;
};
inline Rect GameMapBuilder::RandomRoomRect() {
  Rect ret;
  // Need some space to prevent room adhesion
  ret.w = random_gen_ -> RandomIn(kMinRoomWidth + 2, kMaxRoomWidth + 2);
  ret.h = random_gen_ -> RandomIn(kMinRoomHeight + 2, kMaxRoomHeight + 2);
  return ret;
}
inline const Rect & GameMapBuilder::max(const Rect & a, const Rect & b) {
  if (a.w < 0 || a.h < 0) return b;
  if (b.w < 0 || b.h < 0) return a;
  long long a_area = a.w, b_area = b.w;
  a_area *= a.h, b_area *= b.h;
  if (a_area > b_area) {
    return a;
  } else {
    return b;
  }
}
#endif  // SRC_MAP_GAMEMAP_H_
