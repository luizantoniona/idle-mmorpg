#include "LocationActionLoot.h"

namespace Model {

LocationActionLoot::LocationActionLoot() :
    _id( "" ),
    _baseAmount( 0.0 ),
    _modifierAmount( 0.0 ),
    _baseChance( 0.0 ),
    _modifierChance( 0.0 ) {}

std::string LocationActionLoot::id() const {
    return _id;
}

void LocationActionLoot::setId( const std::string& id ) {
    _id = id;
}

double LocationActionLoot::baseAmount() const {
    return _baseAmount;
}

void LocationActionLoot::setBaseAmount( double baseAmount ) {
    _baseAmount = baseAmount;
}

double LocationActionLoot::modifierAmount() const {
    return _modifierAmount;
}

void LocationActionLoot::setModifierAmount( double modifierAmount ) {
    _modifierAmount = modifierAmount;
}

double LocationActionLoot::baseChance() const {
    return _baseChance;
}

void LocationActionLoot::setBaseChance( double baseChance ) {
    _baseChance = baseChance;
}

double LocationActionLoot::modifierChance() const {
    return _modifierChance;
}

void LocationActionLoot::setModifierChance( double modifierChance ) {
    _modifierChance = modifierChance;
}

double LocationActionLoot::realAmountByLevel( int skillLevel ) const {
    return _baseAmount + _modifierAmount * skillLevel;
}

double LocationActionLoot::realChanceByLevel( int skillLevel ) const {
    return _baseChance + _modifierChance * skillLevel;
}

} // namespace Model
