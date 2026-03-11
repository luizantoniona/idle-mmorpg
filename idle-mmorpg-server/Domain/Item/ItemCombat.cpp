#include "ItemCombat.h"

namespace Domain {

ItemCombat::ItemCombat() :
    _attack( 0.0 ),
    _attackSpeed( 0.0 ),
    _defense( 0.0 ) {
}

Json::Value ItemCombat::toJson() const {
    Json::Value root;
    root[ "attack" ] = attack();
    root[ "attackSpeed" ] = attackSpeed();
    root[ "defense" ] = defense();
    return root;
}

double ItemCombat::attack() const {
    return _attack;
}

void ItemCombat::setAttack( double attack ) {
    _attack = attack;
}

double ItemCombat::attackSpeed() const {
    return _attackSpeed;
}

void ItemCombat::setAttackSpeed( double attackSpeed ) {
    _attackSpeed = attackSpeed;
}

double ItemCombat::defense() const {
    return _defense;
}

void ItemCombat::setDefense( double defense ) {
    _defense = defense;
}

} // namespace Domain
