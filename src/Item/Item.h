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
#ifndef UNNAMING_GAME_SRC_ITEM_ITEM_H_
#define UNNAMING_GAME_SRC_ITEM_ITEM_H_
#include "../Map/Map.h"
class Item final {
 public:
  explicit Item(const Map_ref& origin) : origin_(origin) {}
  const Map_ref& origin() const {return origin_;}
 private:
  const Map_ref origin_;
};
#endif  // UNNAMING_GAME_SRC_ITEM_ITEM_H_
