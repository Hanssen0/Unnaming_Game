#include "CreatureDestroyAction.h"
#include "./creature_action_implementation.h"
#include "../creature_cmake.h"
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
