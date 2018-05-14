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
#include "LivingThings.h"
#include "cstdint"
#include "iostream"
inline uint32_t GetDifference(uint32_t a, uint32_t b) {
  if (a > b) {
    return a - b;
  } else {
    return b - a;
  }
}
inline uint64_t Square(uint32_t a) {
  uint64_t ret = abs(a);
  ret *= ret;
  return ret;
}
// Prevent overflow
inline bool IsAPlusBBiggerThanC(uint64_t a, uint64_t b, uint64_t c) {
  if (a > c && b > c) {
    return true;
  }
  if (a < c) {
    return b > (c - a);
  } else {
    return a > (c - b);
  }
}
inline int64_t UnsignedMinus(uint32_t a, uint32_t b) {
  return static_cast< int64_t >(a) - static_cast< int64_t >(b);
}
inline uint32_t NoNegitiveMinus(uint32_t a, uint32_t b) {
  if (a < b) {
    return 0;
  } else {
    return a - b;
  }
}
inline uint32_t NoOverflowPlus(uint32_t a, uint32_t b, uint32_t up_limit) {
  if (a > up_limit || b > up_limit) return up_limit;
  if (a > up_limit - b) return up_limit;
  return a + b;
}
bool LivingThings::IsAValidMove(const Point & des) {
  if (des.x < 0 || des.y < 0 ||
      des.x >= kMapWidth || des.y >= kMapHeight) {
    return false;
  }
  if (!moveable_[now_map_ -> data(des)]) return false;
  if (GetDifference(des.x, now_pos_.x) + GetDifference(des.y, now_pos_.y)
      <= 1) {
    return true;
  } else {
    return false;
  }
}
// a / b
int64_t RoundingOfAMulBDivideC(int64_t a, int64_t b, int64_t c) {
  if (c == 0) {
    return INT64_MAX;
  }
  bool is_positive = true;
  if (a < 0) {
    is_positive = !is_positive;
    a = -a;
  }
  if (b < 0) {
    is_positive = !is_positive;
    b = -b;
  }
  if (c < 0) {
    is_positive = !is_positive;
    c = -c;
  }
  uint64_t tmp = a * 10;
  tmp *= b;
  tmp /= c;
  if (tmp % 10 < 5) {
    tmp /= 10;
  } else {
    tmp /= 10;
    tmp += 1;
  }
  return (is_positive ? 1 : -1) * tmp;
}
void LivingThings::UpdateViewAble() {
  size_t dis_array_size = (view_dis_ << 1) + 1;
  std::vector< std::vector< bool > > is_tested(dis_array_size, 
                                               std::vector< bool >(
                                                   dis_array_size,
                                                   false));
  std::queue< Point > waiting;
  is_tested[view_dis_][view_dis_] = true;
  waiting.push(TempPoint(view_dis_, view_dis_));
  for (size_t i = 0; i < dis_array_size; ++i) {
    for (size_t j = 0; j < dis_array_size; ++j) {
      viewable_[i][j] = false;
    }
  }
  viewable_[view_dis_][view_dis_] = true;
  // Prevent additional computation
  size_t min_x;
  if (now_pos_.x < view_dis_) {
    min_x = view_dis_ - now_pos_.x; 
  } else {
    min_x = 0;
  }
  size_t min_y;
  if (now_pos_.y < view_dis_) {
    min_y = view_dis_ - now_pos_.y; 
  } else {
    min_y = 0;
  }
  size_t max_x;
  if (now_pos_.x + view_dis_ >= kMapWidth) {
    max_x = view_dis_ + (kMapWidth - 1 - now_pos_.x); 
  } else {
    max_x = dis_array_size - 1;
  }
  size_t max_y;
  if (now_pos_.y + view_dis_ >= kMapHeight) {
    max_y = view_dis_ + (kMapHeight - 1 - now_pos_.y); 
  } else {
    max_y = dis_array_size - 1;
  }
  uint64_t square_view_dis = Square(view_dis_);
  while (!waiting.empty()) {
    Point tmp = waiting.front();
    waiting.pop();
    if (IsAPlusBBiggerThanC(Square(GetDifference(tmp.x, view_dis_)),
                            Square(GetDifference(tmp.y, view_dis_)),
                            square_view_dis)) {
      continue;
    }
    //Four directions
    if (tmp.x >= min_x + 1&& !is_tested[tmp.x - 1][tmp.y]) {
      --tmp.x;
      waiting.push(tmp);
      is_tested[tmp.x][tmp.y] = true;
      ++tmp.x;
    }
    if (tmp.y >= min_y + 1&& !is_tested[tmp.x][tmp.y - 1]) {
      --tmp.y;
      waiting.push(tmp);
      is_tested[tmp.x][tmp.y] = true;
      ++tmp.y;
    }
    if (tmp.x + 1 <= max_x && !is_tested[tmp.x + 1][tmp.y]) {
      ++tmp.x;
      waiting.push(tmp);
      is_tested[tmp.x][tmp.y] = true;
      --tmp.x;
    }
    if (tmp.y + 1 <= max_y && !is_tested[tmp.x][tmp.y + 1]) {
      ++tmp.y;
      waiting.push(tmp);
      is_tested[tmp.x][tmp.y] = true;
      --tmp.y;
    }
    UpdateViewAbleOnALine(UnsignedMinus(tmp.x, view_dis_),
                          UnsignedMinus(tmp.y, view_dis_));
  }
  UpdateMemery();
}
void LivingThings::UpdateViewAbleOnALine(const int64_t end_x, const int64_t end_y) {
  int64_t max_det;
  bool is_postive;
  bool is_x_bigger;
  if (abs(end_x) > abs(end_y)) {
    max_det = end_x;
    is_x_bigger = true;
  } else {
    max_det = end_y;
    is_x_bigger = false;
  }
  if (max_det < 0) {
    is_postive = false;
  } else {
    is_postive = true;
  }
  for (int64_t k = (is_postive ? 1 : -1); k != (max_det + (is_postive ? 1 : -1));
       k += is_postive ? 1 : -1) {
    int64_t min_one;
    if (is_x_bigger) {
      min_one = RoundingOfAMulBDivideC(k , end_y, end_x);
      viewable_[static_cast< int64_t >(view_dis_) + k][static_cast< int64_t >(view_dis_) + min_one] = true;
      if (!see_through_able_[now_map_ -> data(
                                             TempPoint(now_pos_.x + k,
                                                 now_pos_.y + min_one))]) break;
    }else {
      min_one = RoundingOfAMulBDivideC(k , end_x, end_y);
      viewable_[static_cast< int64_t >(view_dis_) + min_one][static_cast< int64_t >(view_dis_) + k] = true;
      if (!see_through_able_[now_map_ -> data(
                                             TempPoint(now_pos_.x + min_one,
                                                 now_pos_.y + k))]) break;
    }
  }
}
LivingThings::LivingThings() {
  now_pos_.x = 0;
  now_pos_.y = 0;
  now_map_ = nullptr;
  view_dis_ = 0;
  for (uint32_t i = 0; i < kBlockMax; ++i) {
    see_through_able_[i] = false;
  }
  for (uint32_t i = 0; i < kBlockMax; ++i) {
    moveable_[i] = false;
  }
}
void LivingThings::UpdateMemery() {
  MemoryOfMap * now;
  auto finder = memories_of_map_.find(now_map_);
  if (finder == memories_of_map_.end()) {
    now = &memories_of_map_[now_map_];
    now -> left_top = TempPoint(kMapWidth, kMapHeight);
    now -> right_bottom = TempPoint(0, 0);
    for (uint32_t i = 0; i < kMapWidth; ++i) {
      for (uint32_t j = 0; j < kMapHeight; ++j) {
        now -> is_seen[i][j] = false;
      }
    }
  } else {
    now = &(finder -> second);
  }
  now -> left_top = TempPoint(std::min(now -> left_top.x,
                                       NoNegitiveMinus(now_pos_.x, view_dis_)),
                              std::min(now -> left_top.y,
                                       NoNegitiveMinus(now_pos_.y, view_dis_)));
  now -> right_bottom = TempPoint(std::max(now -> right_bottom.x,
                                           NoOverflowPlus(now_pos_.x,
                                                          view_dis_,
                                                          kMapWidth - 1)),
                                  std::max(now -> right_bottom.y,
                                           NoOverflowPlus(now_pos_.y,
                                                          view_dis_,
                                                          kMapHeight - 1)));
  size_t max_x = std::min(static_cast< uint64_t >(viewable_size() - 1),
                          static_cast< uint64_t >(kMapWidth - now_pos_.x - 1) +
                          view_dis_);
  size_t max_y = std::min(static_cast< uint64_t >(viewable_size() - 1),
                          static_cast< uint64_t >(kMapHeight - now_pos_.y - 1) + 
                          view_dis_);
  for (size_t i = NoNegitiveMinus(view_dis_, now_pos_.x); i <= max_x; ++i) {
    for (size_t j = NoNegitiveMinus(view_dis_, now_pos_.y); j <= max_y; ++j) {
      if (viewable_[i][j]) {
        Point writing_point;
        ViewPosToRealPos(TempPoint(i, j), &writing_point);
        if (!now -> is_seen[writing_point.x][writing_point.y]) {
          now -> detail.set_data(writing_point, now_map_ -> data(writing_point));
          now -> detail.set_building(writing_point, now_map_ -> building(writing_point));
          now -> is_seen[writing_point.x][writing_point.y] = true;
        }
      }
    }
  }
}
