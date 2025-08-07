#include "CreatureLoot.h"

namespace Model {

CreatureLoot::CreatureLoot() :
    _id( "" ),
    _chance( 0.0 ),
    _amount( 0 ) {}

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

int CreatureLoot::amount() const {
    return _amount;
}

void CreatureLoot::setAmount( int amount ) {
    _amount = amount;
}

} // namespace Model
