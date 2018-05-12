#ifndef SRC_OBJECT_LIVINGTHING_H_
#define SRC_OBJECT_LIVINGTHING_H_
#include "../Map/GameMap.h"
enum LivingThingsRace {
  kLivingThingsHuman
};
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
  inline void set_view_dis(const int & d) {
    viewable_.resize((d << 1) + 1, std::vector< bool >((d << 1> + 1, false)));
    view_dis_ = d;
  }
  inline int view_dis() {return view_dis_;}
  inline void set_viewable(const Point & pos, const bool & s) {
    viewable_[pos.x][pos.y] = s;
  }
  inline bool viewable(const Point & pos) {return viewable_[pos.x][pos.y];}
  inline void set_see_through_able(const BlockType & t, const bool & s) {
    see_through_able_[t] = s;
  }
  inline void GoTo(const Point & des) {
    if (IsAValidMove(des)) {
      now_pos_ = des;
    }
  }
  void UpdateViewAble(const Point & now);
 private:
  bool IsAValidMove(const Point & des);
  void UpdateViewAbleOnALine(const Point & now, 
                             const Point & end_when_origin_is_now);
  LivingThingsRace race_;
  GameMap * now_map_;
  Point now_pos_;
  bool moveable_[kBlockMax];
  bool see_through_able_[kBlockMax];
  int view_dis_;
  std::vector< std::vector< bool > > viewable_;
};
#endif  // SRC_OBJECT_LIVINGTHING_H_

