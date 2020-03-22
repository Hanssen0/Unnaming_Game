// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "Pathfinder.h"
#include <algorithm>
MapPoint evaulate_to;
inline size_t abs_minus(size_t a, size_t b) {
  return a > b ? a - b : b - a;
}
void PathFinder::set_target_map(const Map& target) {
  target_map_ = &target;
  walked_.resize(target.Width());
  walked_dis_.resize(target.Width());
  is_first_check_.resize(target.Width());
  father_.resize(target.Width());
  for (size_t i = 0; i < target.Height(); ++i) {
    walked_[i].resize(target.Height());
    walked_dis_[i].resize(target.Height());
    is_first_check_[i].resize(target.Height());
    father_[i].resize(target.Height());
  }
}
inline uint64_t EvaulateValue(const MapPoint& po) {
  return abs_minus(po.x, evaulate_to.x) + abs_minus(po.y, evaulate_to.y);
}
std::list<MapPoint> PathFinder::FindShortestPath(const MapPoint& from,
                                                 const MapPoint& to) {
  for (size_t i = 0; i < target_map_->Width(); ++i) {
    for (size_t j = 0; j < target_map_->Height(); ++j) {
      is_first_check_[i][j] = true;
    }
  }
  for (size_t i = 0; i < target_map_->Width(); ++i) {
    for (size_t j = 0; j < target_map_->Height(); ++j) {
      walked_[i][j] = false;
    }
  }
  evaulate_to = to;
  walked_dis_[from.x][from.y] =
      static_cast< uint64_t >(value_[target_map_->BlockIn(from)->index()]);
  father_[from.x][from.y] = from;
  searching_list.push_back(from);
  MapPoint min_dis;
  while (!searching_list.empty()) {
    min_dis = searching_list.front();
    searching_list.pop_front();
    if (min_dis.x == to.x && min_dis.y == to.y) {
      break;
    }
    UpdateNearby(min_dis);
  }
  std::list<MapPoint> shortest_path;
  MapPoint backer;
  if (min_dis.x == to.x && min_dis.y == to.y) {
    backer = to;
    while (!(backer == father_[backer.x][backer.y])) {
      shortest_path.push_front(backer);
      backer = father_[backer.x][backer.y];
    }
  }
  return shortest_path;
}
void PathFinder::UpdateNearby(const MapPoint& now) {
  walked_[now.x][now.y] = true;
  MapPoint tmp = now;
  if (tmp.x > 0) {
    --tmp.x;
    if (TryAPoint(target_map_->BlockIn(tmp),
                  walked_dis_[now.x][now.y] +
                  (father_[now.x][now.y].x - 1 == now.x ? 0 : 1),
                  tmp)) {
      father_[tmp.x][tmp.y] = now;
    }
    ++tmp.x;
  }
  if (tmp.y > 0) {
    --tmp.y;
    if (TryAPoint(target_map_->BlockIn(tmp),
                  walked_dis_[now.x][now.y] +
                  (father_[now.x][now.y].y - 1 == now.y ? 0 : 1),
                  tmp)) {
      father_[tmp.x][tmp.y] = now;
    }
    ++tmp.y;
  }
  if (tmp.x < target_map_->Width() - 1) {
    ++tmp.x;
    if (TryAPoint(target_map_->BlockIn(tmp),
                  walked_dis_[now.x][now.y] +
                  (father_[now.x][now.y].x + 1 == now.x ? 0 : 1),
                  tmp)) {
      father_[tmp.x][tmp.y] = now;
    }
    --tmp.x;
  }
  if (tmp.y < target_map_->Height() - 1) {
    ++tmp.y;
    if (TryAPoint(target_map_->BlockIn(tmp),
                  walked_dis_[now.x][now.y] +
                  (father_[now.x][now.y].y + 1 == now.y ? 0 : 1),
                  tmp)) {
      father_[tmp.x][tmp.y] = now;
    }
    --tmp.y;
  }
}
bool PathFinder::TryAPoint(const BlockPtr& type, uint64_t walked_dis,
                           const MapPoint& now) {
  if (!walked_[now.x][now.y] && value_[type->index()] >= 0) {
    auto now_dis = walked_dis +
                   static_cast<unsigned int>(value_[type->index()]);
    if (is_first_check_[now.x][now.y] == true) {
      walked_dis_[now.x][now.y] = now_dis;
      PushPointToAstarList(now);
      is_first_check_[now.x][now.y] = false;
      return true;
    }
    if (walked_dis_[now.x][now.y] > now_dis) {
      walked_dis_[now.x][now.y] = now_dis;
      searching_list.erase(std::find(searching_list.begin(),
                                     searching_list.end(),
                                     now));
      PushPointToAstarList(now);
      return true;
    }
  }
  return false;
}
void PathFinder::PushPointToAstarList(const MapPoint& po) {
  std::list<MapPoint>::iterator now = searching_list.begin();
  while (now != searching_list.end() &&
         walked_dis_[(*now).x][(*now).y] + EvaulateValue(*now) <
         walked_dis_[po.x][po.y] + EvaulateValue(po)) {
    ++now;
  }
  searching_list.insert(now, po);
}
