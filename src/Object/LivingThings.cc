#include "LivingThings.h"
#include "../CPP.h"
bool LivingThings::IsAValidMove(const Point & des) {
  if (des.x < 0 || des.y < 0 ||
      des.x > kMapWidth - 1 || des.y > kMapHeight - 1) {
    return false;
  }
  if (!moveable_[now_map_ -> data(des.x, des.y)]) return false;
  if (abs(des.x - now_pos_.x) + abs(des.y - now_pos_.y) <= 1) {
    return true;
  } else {
    return false;
  }
}
// a / b
int RoundingOfDivide(int a, int b) {
  if (b == 0) {
    return INT_MAX;
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
  long long tmp = a * 10;
  tmp /= b;
  if (tmp % 10 < 5) {
    return (is_positive ? 1 : -1) * tmp / 10;
  } else {
    return (is_positive ? 1 : -1) * ((tmp / 10) + 1);
  }
}
void LivingThings::UpdateViewAble(const Point & now) {
  long long square_view_dis = view_dis_ * view_dis_;
  int dis_array_size = (view_dis_ << 1) + 1;
  std::vector< std::vector< bool > > is_tested(dis_array_size, 
                                               std::vector< bool >(
                                                   dis_array_size,
                                                   false));
  std::queue< Point > waiting;
  {
    Point tmp;
    tmp.x = view_dis_;
    tmp.y = view_dis_;
    is_tested[tmp.x][tmp.y] = true;
    waiting.push(tmp);
  }
  for (int i = 0; i < dis_array_size; ++i) {
    for (int j = 0; j < dis_array_size; ++j) {
      viewable_[i][j] = false;
    }
  }
  viewable_[view_dis_][view_dis_] = true;
  int min_x = std::max(0, view_dis_ - now.x);
  int min_y = std::max(0, view_dis_ - now.y);
  int max_x = std::min(dis_array_size - 1, view_dis_ + (kMapWidth  - 1 - now.x));
  int max_y = std::min(dis_array_size - 1, view_dis_ + (kMapHeight - 1 - now.y));
  while (!waiting.empty()) {
    Point tmp = waiting.front();
    Point origin_is_now;
    origin_is_now.x = tmp.x - view_dis_;
    origin_is_now.y = tmp.y - view_dis_;
    waiting.pop();
    if (static_cast<long long>(origin_is_now.x) * (origin_is_now.x) +
        static_cast<long long>(origin_is_now.y) * (origin_is_now.y) >
        square_view_dis) {
      continue;
    }
    --tmp.x;
    if (tmp.x >= min_x && !is_tested[tmp.x][tmp.y]) {
      waiting.push(tmp);
      is_tested[tmp.x][tmp.y] = true;
    }
    ++tmp.x;
    --tmp.y;
    if (tmp.y >= min_y && !is_tested[tmp.x][tmp.y]) {
      waiting.push(tmp);
      is_tested[tmp.x][tmp.y] = true;
    }
    ++tmp.y;
    ++tmp.x;
    if (tmp.x <= max_x && !is_tested[tmp.x][tmp.y]) {
      waiting.push(tmp);
      is_tested[tmp.x][tmp.y] = true;
    }
    --tmp.x;
    ++tmp.y;
    if (tmp.y <= max_y && !is_tested[tmp.x][tmp.y]) {
      waiting.push(tmp);
      is_tested[tmp.x][tmp.y] = true;
    }
    --tmp.y;
    UpdateViewAbleOnALine(now, origin_is_now);
  }
}
void LivingThings::UpdateViewAbleOnALine(const Point & now,
                                         const Point & end_when_origin_is_now) {
  int max_det;
  bool is_postive;
  bool is_x_bigger;
  if (abs(end_when_origin_is_now.x) > abs(end_when_origin_is_now.y)) {
    max_det = end_when_origin_is_now.x;
    is_x_bigger = true;
  } else {
    max_det = end_when_origin_is_now.y;
    is_x_bigger = false;
  }
  if (max_det < 0) {
    is_postive = false;
  } else {
    is_postive = true;
  }
  for (int k = (is_postive ? 1 : -1); k != (max_det + (is_postive ? 1 : -1));
       k += is_postive ? 1 : -1) {
    int min_one;
    if (is_x_bigger) {
      min_one = RoundingOfDivide(k * end_when_origin_is_now.y, end_when_origin_is_now.x);
      viewable_[view_dis_ + k][view_dis_ + min_one] = true;
      if (!see_through_able_[now_map_ -> data(now.x + k,
                                              now.y + min_one)]) break;
    }else {
      min_one = RoundingOfDivide(k * end_when_origin_is_now.x, end_when_origin_is_now.y);
      viewable_[view_dis_ + min_one][view_dis_ + k] = true;
      if (!see_through_able_[now_map_ -> data(now.x + min_one, 
                                              now.y + k)]) break;
    }
  }
}
