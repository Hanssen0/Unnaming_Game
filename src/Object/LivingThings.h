#ifndef UNNAMING_GAME_SRC_OBJECT_LIVINGTHING_H_
#define UNNAMING_GAME_SRC_OBJECT_LIVINGTHING_H_
#include "../Map/GameMap.h"
enum LivingThingsRace {
  kLivingThingsHuman
};
const uint32_t kSquareRootOfINT64MAX = 3037000499;
class LivingThings {
 public:
  inline LivingThingsRace race() {return race_;}
  inline void set_race(const LivingThingsRace & r) {race_ = r;}
  inline void set_now_map(GameMap * map) {now_map_ = map;}
  inline void set_now_pos(const Point & pos) {now_pos_ = pos;}
  inline Point now_pos() {return now_pos_;}
  inline void set_moveable(const BlockType & t, const bool & s) {
    moveable_[t] = s;
  }
  inline bool set_view_dis(const uint32_t & d) {
    // Prevent overflow
    if ((SIZE_MAX - 1) >> 1 < d || kSquareRootOfINT64MAX < d) return false; 
    viewable_.resize((static_cast< size_t >(d) << 1) + 1,
                     std::vector< bool >((static_cast< size_t >(d) << 1) + 1,
                                         false));
    view_dis_ = d;
    return true;
  }
  inline uint32_t view_dis() {return view_dis_;}
  inline void set_viewable(const Point & pos, const bool & s) {
    viewable_[pos.x][pos.y] = s;
  }
  inline bool viewable(const Point & pos) {
    if (pos.x < viewable_.size() && pos.y < viewable_.size()) {
      return viewable_[pos.x][pos.y];
    } else {
      return false;
    }
  }
  inline void set_see_through_able(const BlockType & t, const bool & s) {
    see_through_able_[t] = s;
  }
  inline void GoTo(const Point & des) {
    if (IsAValidMove(des)) {
      now_pos_ = des;
    }
  }
  void UpdateViewAble(const Point & now);
  LivingThings();
 private:
  bool IsAValidMove(const Point & des);
  void UpdateViewAbleOnALine(const Point & now, 
                             const int64_t end_x,
                             const int64_t end_y);
  LivingThingsRace race_;
  GameMap * now_map_;
  Point now_pos_;
  bool moveable_[kBlockMax];
  bool see_through_able_[kBlockMax];
  uint32_t view_dis_;
  std::vector< std::vector< bool > > viewable_;
};
#endif  // UNNAMING_GAME_SRC_OBJECT_LIVINGTHING_H_
