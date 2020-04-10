#include "CreatureAction.h"
#include "./creature_action_implementation.h"
#include "../creature_cmake.h"
CREATURE_EXPORT Creature::Action::Action(
    const std::shared_ptr< Creature::Action::Implementation >& impl)
    : impl_(impl) {}
CREATURE_EXPORT void Creature::Action::Perform(
    const Map_ref& map, const MapPoint& pos,
    Creature* const creature) const {impl_->Perform(map, pos, creature);}
