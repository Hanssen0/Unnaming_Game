#include "LivingThings.h"
#include "../CPP.h"
void LivingThings::GoTo(const Point & des) {
  if (IsAValidMove(des)) {
    now_pos_ = des;
  }
}
bool LivingThings::IsAValidMove(const Point & des) {
  if (!moveable_[now_map_ -> data(des.x, des.y)]) return false;
  if (abs(des.x - now_pos_.x) + abs(des.y - now_pos_.y) <= 1) {
    return true;
  } else {
    return false;
  }
}
// a / b
int RoundingOfDivide(int a, int b) {
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
  int square_view_dis = view_dis_ * view_dis_;
  int max_x = std::min(view_dis_, kMapWidth - now.x - 1);
  int max_y = std::min(view_dis_, kMapHeight - now.y - 1);
  for (int i = std::max(-view_dis_, -now.x); i <= max_x; ++i) {
    for (int j = std::max(-view_dis_, -now.y); j <= max_y; ++j) {
      if (viewable_[now.x + i][now.y + j]) continue;
      if (abs(i) * abs(i) + abs(j) * abs(j) > square_view_dis) {
        if (j < 0) {
          continue;
        } else {
          break;
        }
      }
      int max_det;
      bool is_postive;
      bool is_i_bigger;
      if (abs(i) > abs(j)) {
        max_det = i;
        is_i_bigger = true;
      } else {
        max_det = j;
        is_i_bigger = false;
      }
      if (max_det < 0) {
        is_postive = false;
      } else {
        is_postive = true;
      }
      for (int k = 0; k != (max_det + (is_postive ? 1 : -1));
           k += is_postive ? 1 : -1) {
        int min_one;
        if (is_i_bigger) {
          min_one = RoundingOfDivide(k * j, i);
          if (!see_through_able_[now_map_ -> data(now.x + k,
                                                  now.y + min_one)]) break;
          viewable_[now.x + k][now.y + min_one] = true;
        }else {
          min_one = RoundingOfDivide(k * i, j);
          if (!see_through_able_[now_map_ -> data(now.x + min_one, 
                                                  now.y + k)]) break;
          viewable_[now.x + min_one][now.y + k] = true;
        }
      }
    }
  }
}
