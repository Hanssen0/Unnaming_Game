#include "Pathfinder.h"
#include <algorithm>
Point evaulate_to;
void PathFinder::set_target_map(Map& target) {
  target_map_ = &target;
  walked_.resize(target.Width());
  walked_dis_.resize(target.Width());
  is_first_check_.resize(target.Width());
  father_.resize(target.Width());
  for (int32_t i = 0; i < target.Height(); ++i) {
    walked_[i].resize(target.Height());
  }
  for (int32_t i = 0; i < target.Height(); ++i) {
    walked_dis_[i].resize(target.Height());
  }
  for (int32_t i = 0; i < target.Height(); ++i) {
    is_first_check_[i].resize(target.Height());
  }
  for (int32_t i = 0; i < target.Height(); ++i) {
    father_[i].resize(target.Height());
  }
}
inline uint32_t EvaulateValue(const Point& po) {
  uint32_t ret = abs(po.x - evaulate_to.x) + abs(po.y - evaulate_to.y);
  return ret;
}
std::list< Point > PathFinder::FindShortestPath(const Point& from,
                                                const Point& to) {
  for (int32_t i = 0; i < target_map_ -> Width(); ++i) {
    for (int32_t j = 0; j < target_map_ -> Height(); ++j) {
      is_first_check_[i][j] = true;
    }
  }
  for (int32_t i = 0; i < target_map_ -> Width(); ++i) {
    for (int32_t j = 0; j < target_map_ -> Height(); ++j) {
      walked_[i][j] = false;
    }
  }
  evaulate_to = to;
  walked_dis_[from.x][from.y] =
      static_cast< uint64_t >(value_[target_map_ -> Block(from)]);
  father_[from.x][from.y] = from;
  searching_list.push_back(from);
  Point min_dis;
  while (!searching_list.empty()) {
    min_dis = searching_list.front();
    searching_list.pop_front();
    if (min_dis.x == to.x && min_dis.y == to.y) {
      break;
    }
    UpdateNearby(min_dis);
  }
  std::list< Point > shortest_path;
  Point backer;
  if (min_dis.x == to.x && min_dis.y == to.y) {
    backer = to;
    while (!(backer == father_[backer.x][backer.y])) {
      shortest_path.push_front(backer);
      backer = father_[backer.x][backer.y];
    }
  }
  return shortest_path;
}
void PathFinder::UpdateNearby(const Point& now) {
  walked_[now.x][now.y] = true;
  Point tmp = now;
  if (tmp.x > 0) {
    --tmp.x;
    if (TryAPoint(target_map_ -> Block(tmp),
                  walked_dis_[now.x][now.y] +
                  (father_[now.x][now.y].x - 1 == now.x ? 0 : 1),
                  tmp)) {
      father_[tmp.x][tmp.y] = now;
    }
    ++tmp.x;
  }
  if (tmp.y > 0) {
    --tmp.y;
    if (TryAPoint(target_map_ -> Block(tmp),
                  walked_dis_[now.x][now.y] +
                  (father_[now.x][now.y].y - 1 == now.y ? 0 : 1),
                  tmp)) {
      father_[tmp.x][tmp.y] = now;
    }
    ++tmp.y;
  }
  if (tmp.x < target_map_ -> Width() - 1) {
    ++tmp.x;
    if (TryAPoint(target_map_ -> Block(tmp),
                  walked_dis_[now.x][now.y] +
                  (father_[now.x][now.y].x + 1 == now.x ? 0 : 1),
                  tmp)) {
      father_[tmp.x][tmp.y] = now;
    }
    --tmp.x;
  }
  if (tmp.y < target_map_ -> Height() - 1) {
    ++tmp.y;
    if (TryAPoint(target_map_ -> Block(tmp),
                  walked_dis_[now.x][now.y] +
                  (father_[now.x][now.y].y + 1 == now.y ? 0 : 1),
                  tmp)) {
      father_[tmp.x][tmp.y] = now;
    }
    --tmp.y;
  }
}
bool PathFinder::TryAPoint(const Map::BlockType type, uint64_t walked_dis,
                           const Point& now) {
  if (!walked_[now.x][now.y] && value_[type] >= 0) {
    if (is_first_check_[now.x][now.y] == true) {
      walked_dis_[now.x][now.y] = walked_dis + value_[type];
      PushPointToAstarList(now);
      is_first_check_[now.x][now.y] = false;
      return true;
    }
    if (walked_dis_[now.x][now.y] > walked_dis + value_[type]) {
      walked_dis_[now.x][now.y] = walked_dis + value_[type];
      searching_list.erase(std::find(searching_list.begin(),
                                     searching_list.end(),
                                     now));
      PushPointToAstarList(now);
      return true;
    }
  }
  return false;
}
void PathFinder::PushPointToAstarList(const Point& po) {
  std::list< Point >::iterator now = searching_list.begin();
  while (now != searching_list.end() &&
         walked_dis_[(*now).x][(*now).y] + EvaulateValue(*now) <
         walked_dis_[po.x][po.y] + EvaulateValue(po)) {
    ++now;
  }
  searching_list.insert(now, po);
}
