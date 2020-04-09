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
#ifndef UNNAMING_GAME_SRC_MAP_SPACE_H_
#define UNNAMING_GAME_SRC_MAP_SPACE_H_
#include <map>
#include <cassert>
#include <functional>
#include <list>
#include <vector>
#include "./Building/Building.h"
#include "./Map.h"
#include "../Logic/MapBuilder.h"
class Space {
 public:
  inline Space(const Space& space): builder_(space.builder_),
                                    next_map_size_(space.next_map_size_) {}
  inline Space(MapBuilder* builder, const Rect& nms,
               const std::function<size_t(size_t, size_t)>& ran)
      : builder_(builder), next_map_size_(nms), random_(ran) {}
  inline void set_next_map_size(const Rect& si) {next_map_size_ = si;}
  inline const std::function<size_t(size_t, size_t)>& random() {return random_;}
  Map_ref NewMap();

 private:
  MapBuilder* const builder_;
  std::list<Map_ref> maps_;
  Rect next_map_size_;
  const std::function<size_t(size_t, size_t)> random_;
};
#endif  // UNNAMING_GAME_SRC_MAP_SPACE_H_
