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
#ifndef UNNAMING_GAME_SRC_OBJECT_LIVINGTHING_H_
#define UNNAMING_GAME_SRC_OBJECT_LIVINGTHING_H_
#include "../Map/GameMap.h"
enum LivingThingsRace {
  kLivingThingsHuman,
  kLivingThingsMax
};
const uint32_t kSquareRootOfINT64MAX = 3037000499;
class LivingThings {
 public:
  inline void set_race(const LivingThingsRace & r) {race_ = r;}
  inline LivingThingsRace race() const {return race_;}
  inline void set_now_map(GameMap * map) {now_map_ = map;}
  inline GameMap * now_map() const {return now_map_;}
  inline void set_now_pos(const Point & pos) {now_pos_ = pos;}
  inline Point now_pos() const {return now_pos_;}
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
  inline uint32_t view_dis() const {return view_dis_;}
  inline void set_viewable(const Point & pos, const bool & s) {
    viewable_[pos.x][pos.y] = s;
  }
  inline bool viewable(const Point & pos) const {
    if (pos.x < viewable_.size() && pos.y < viewable_.size()) {
      return viewable_[pos.x][pos.y];
    } else {
      return false;
    }
  }
  inline size_t viewable_size() const {return viewable_.size();}
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
