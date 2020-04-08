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
#ifndef UNNAMING_GAME_SRC_OBJECT_ABILITY_H_
#define UNNAMING_GAME_SRC_OBJECT_ABILITY_H_
#include <cmath>
#include <list>
#include "../Common/Point.h"
#include "../Map/Building/Building.h"
#include "../Map/Map.h"
class Creature;
class Action {
 public:
  virtual void Perform(
      const Map_ref&, const MapPoint&,
      const Creature* const) const = 0;
};
class DestroyAction : public Action {
 public:
  virtual void Perform(
      const Map_ref& place, const MapPoint& location,
      const Creature* const) const {
    assert(place->has(location));
    place->DestroyGroundIn(location);
  }
};
#endif  // UNNAMING_GAME_SRC_OBJECT_ABILITY_H_
