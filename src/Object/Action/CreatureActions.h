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
#ifndef UNNAMING_GAME_SRC_OBJECT_ACTION_CREATUREACTIONS_H_
#define UNNAMING_GAME_SRC_OBJECT_ACTION_CREATUREACTIONS_H_
#include <memory>
#include "./CreatureAction.h"
#include "../Creature.h"
#include "../../Map/Map.h"
class CreatureDestroyAction {
 public:
  class Implementation;
  CreatureDestroyAction();
  void Perform(const Map_ref&, const MapPoint&, Creature* const) const;
  operator Creature::Action() const;

 private:
  std::shared_ptr<Implementation> impl_;
};
class CreatureGatherAction {
 public:
  class Implementation;
  CreatureGatherAction();
  void Perform(const Map_ref&, const MapPoint&, Creature* const) const;
  operator Creature::Action() const;

 private:
  std::shared_ptr<Implementation> impl_;
};
class CreatureMoveAction {
 public:
  class Implementation;
  CreatureMoveAction();
  void Perform(const Map_ref&, const MapPoint&, Creature* const) const;
  operator Creature::Action() const;

 private:
  std::shared_ptr<Implementation> impl_;
};
#endif  // UNNAMING_GAME_SRC_OBJECT_ACTION_CREATUREACTIONS_H_
