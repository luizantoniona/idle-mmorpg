#include "ItemCombat.h"

namespace Domain {

ItemCombat::ItemCombat() :
    _attack( 0.0 ),
    _defense( 0.0 ) {}

Json::Value ItemCombat::toJson() const {
    Json::Value root;
    root[ "attack" ] = attack();
    root[ "defense" ] = defense();
    return root;
}

double ItemCombat::attack() const {
    return _attack;
}

void ItemCombat::setAttack( double attack ) {
    _attack = attack;
}

double ItemCombat::defense() const {
    return _defense;
}

void ItemCombat::setDefense( double defense ) {
    _defense = defense;
}

} // namespace Domain
