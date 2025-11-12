#include "CreatureLoot.h"

namespace Domain {

CreatureLoot::CreatureLoot() :
    _id( "" ),
    _chance( 0.0 ),
    _minAmount( 0 ),
    _maxAmount( 0 ) {
}

std::string CreatureLoot::id() const {
    return _id;
}

void CreatureLoot::setId( const std::string& id ) {
    _id = id;
}

double CreatureLoot::chance() const {
    return _chance;
}

void CreatureLoot::setChance( double chance ) {
    _chance = chance;
}

int CreatureLoot::minAmount() const {
    return _minAmount;
}

void CreatureLoot::setMinAmount( int minAmount ) {
    _minAmount = minAmount;
}

int CreatureLoot::maxAmount() const {
    return _maxAmount;
}

void CreatureLoot::setMaxAmount( int maxAmount ) {
    _maxAmount = maxAmount;
}

} // namespace Domain
