#include "StageCreature.h"

namespace Domain {

StageCreature::StageCreature() :
    _id( "" ),
    _amount( 0 ),
    _creature( nullptr ) {
}

StageCreature::~StageCreature() = default;

std::string StageCreature::id() const {
    return _id;
}

void StageCreature::setId( const std::string& id ) {
    _id = id;
}

int StageCreature::amount() const {
    return _amount;
}

void StageCreature::setAmount( int amount ) {
    _amount = amount;
}

const Creature* StageCreature::creature() const {
    return _creature;
}

void StageCreature::setCreature( const Creature* creature ) {
    _creature = creature;
}

} // namespace Domain
