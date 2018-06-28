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
#include "LivingThing.h"
#include "../Map/Map.h"
#include <queue>
int32_t LivingThing::kLivingThingSize = 0;
constexpr int32_t LivingThing::kMaxViewDis;
inline const int64_t Square(const int32_t& in) {
  return static_cast< int64_t >(in) * static_cast< int64_t >(in);
}
inline const int32_t GetDifference(const int32_t& a, const int32_t& b) {
  if (a > b) return a - b;
  return b - a;
}
inline const bool IsAPlusBBiggerThanC(const int64_t& a, const int64_t& b,
                                      const int64_t& c) {
  if (a > c && b > c) {
    return true;
  }
  if (a < c) {
    return b > (c - a);
  } else {
    return a > (c - b);
  }
}
inline const int32_t RoundingOfAMulBDivideC(int32_t a, int32_t b, int32_t c) {
  if (c == 0) {
    return INT32_MAX;
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
  int64_t tmp = a * 10;
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
void LivingThing::UpdateViewAbleOnALine(const Point& end) {
  int32_t max_det;
  bool is_postive;
  bool is_x_bigger;
  if (abs(end.x) > abs(end.y)) {
    max_det = end.x;
    is_x_bigger = true;
  } else {
    max_det = end.y;
    is_x_bigger = false;
  }
  if (max_det < 0) {
    is_postive = false;
  } else {
    is_postive = true;
  }
  int32_t energy = view_dis();
  for (int32_t k = (is_postive ? 1 : -1); k != (max_det + (is_postive ? 1 : -1));
       k += is_postive ? 1 : -1) {
    int32_t min_one;
    if (is_x_bigger) {
      min_one = RoundingOfAMulBDivideC(k , end.y, end.x);
      is_viewable_[view_dis() + k][view_dis() + min_one] = true;
      const int32_t c_s = cost(now_map().block(CreatePoint(
                                                   now_pos().x + k,
                                                   now_pos().y + min_one))).
                                                       see_through;
      if (c_s < 0) break;
      energy -= c_s;
      if (energy <= 0) break;
    }else {
      min_one = RoundingOfAMulBDivideC(k , end.x, end.y);
      is_viewable_[view_dis() + min_one][view_dis() + k] = true;
      const int32_t c_s = cost(now_map().block(CreatePoint(
                                                   now_pos().x + min_one,
                                                   now_pos().y + k))).
                                                       see_through;
      if (c_s < 0) break;
      energy -= c_s;
      if (energy <= 0) break;
    }
  }
}
void LivingThing::UpdateViewable() {
  const size_t dis_array_size = is_viewable_.size();
  std::vector< std::vector< bool > > is_tested(dis_array_size, 
                                               std::vector< bool >(
                                                   dis_array_size,
                                                   false));
  std::queue< Point > waiting;
  is_tested[view_dis()][view_dis()] = true;
  waiting.push(CreatePoint(view_dis(), view_dis()));
  for (size_t i = 0; i < dis_array_size; ++i) {
    for (size_t j = 0; j < dis_array_size; ++j) {
      is_viewable_[i][j] = false;
    }
  }
  is_viewable_[view_dis()][view_dis()] = true;
  // Prevent additional computation
  const int32_t min_x = now_pos().x < view_dis() ? view_dis() - now_pos().x : 0;
  const int32_t min_y = now_pos().y < view_dis() ? view_dis() - now_pos().y : 0;
  const int32_t max_x = now_pos().x + view_dis() >= now_map().width() ?
                            view_dis() + (now_map().width() - 1 - now_pos().x) :
                            dis_array_size - 1;
  const int32_t max_y = now_pos().y + view_dis() >= now_map().height() ?
                            view_dis() + (now_map().height() - 1 - now_pos().y) :
                            dis_array_size - 1;
  int64_t square_view_dis = Square(view_dis());
  while (!waiting.empty()) {
    Point tmp = waiting.front();
    waiting.pop();
    if (IsAPlusBBiggerThanC(Square(GetDifference(tmp.x, view_dis())),
                            Square(GetDifference(tmp.y, view_dis())),
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
    tmp.x -= view_dis();
    tmp.y -= view_dis();
    UpdateViewAbleOnALine(tmp);
  }
  UpdateMemory();
}
void LivingThing::UpdateMemory() {
  World::MemoryOfMap& now_mem = GetMemory();
  for (size_t i = 0; i < is_viewable_.size(); ++i) {
    for (size_t j = 0; j < is_viewable_.size(); ++j) {
      if (is_viewable_[i][j]) {
        const Point tmp = {now_pos().x - view_dis() +
                           static_cast< int32_t >(i),
                           now_pos().y - view_dis() +
                           static_cast< int32_t >(j)};
        now_mem.left_top.x = std::min(now_mem.left_top.x, tmp.x);
        now_mem.left_top.y = std::min(now_mem.left_top.y, tmp.y);
        now_mem.right_bottom.x = std::max(now_mem.right_bottom.x, tmp.x);
        now_mem.right_bottom.y = std::max(now_mem.right_bottom.y, tmp.y);
        now_mem.is_seen[tmp.x][tmp.y] = true;
        now_mem.detail.set_block(tmp, now_map().block(tmp));
      }
    }
  }
}
