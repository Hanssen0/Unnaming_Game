#include "CreatureActions.h"
#include "./creature_action_implementation.h"
#include "../creature_cmake.h"
#include "../../Item/Item.h"
class CreatureDestroyAction::Implementation
    : public Creature::Action::Implementation {
 public:
  void Perform(
      const Map_ref& place, const MapPoint& location,
      Creature* const) const override {
    if (place->has(location)) place->DestroyGroundIn(location);
  }
};
CREATURE_EXPORT CreatureDestroyAction::CreatureDestroyAction()
    : impl_(std::make_shared<Implementation>()) {}
CREATURE_EXPORT void CreatureDestroyAction::Perform(
    const Map_ref& map, const MapPoint& pos,
    Creature* const creature) const {impl_->Perform(map, pos, creature);}
CREATURE_EXPORT CreatureDestroyAction::operator Creature::Action() const {
  return Creature::Action(impl_);
}
class CreatureGatherAction::Implementation
    : public Creature::Action::Implementation {
 public:
  void Perform(
      const Map_ref& place, const MapPoint&,
      Creature* const creature) const override {
    creature->Obtain(Item(place));
  }
};
CREATURE_EXPORT CreatureGatherAction::CreatureGatherAction()
    : impl_(std::make_shared<Implementation>()) {}
CREATURE_EXPORT void CreatureGatherAction::Perform(
    const Map_ref& map, const MapPoint& pos,
    Creature* const creature) const {impl_->Perform(map, pos, creature);}
CREATURE_EXPORT CreatureGatherAction::operator Creature::Action() const {
  return Creature::Action(impl_);
}
class CreatureMoveAction::Implementation
    : public Creature::Action::Implementation {
 public:
  void Perform(
      const Map_ref& place, const MapPoint& location,
      Creature* const creature) const override {
    if (place->has(location) &&
        place->GroundIn(location).CostMove(*creature) >= 0) {
      creature->SetPosition(location);
    }
  }
};
CREATURE_EXPORT CreatureMoveAction::CreatureMoveAction()
    : impl_(std::make_shared<Implementation>()) {}
CREATURE_EXPORT void CreatureMoveAction::Perform(
    const Map_ref& map, const MapPoint& pos,
    Creature* const creature) const {impl_->Perform(map, pos, creature);}
CREATURE_EXPORT CreatureMoveAction::operator Creature::Action() const {
  return Creature::Action(impl_);
}
