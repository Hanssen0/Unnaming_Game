#include "CreatureGatherAction.h"
#include "./creature_action_implementation.h"
#include "../creature_cmake.h"
#include "../../Item/Item.h"
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
