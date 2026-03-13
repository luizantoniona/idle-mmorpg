#include "CreatureCombat.h"

namespace Domain {

CreatureCombat::CreatureCombat() :
    _attack( 0.0 ),
    _defense( 0.0 ),
    _attackCounter( 0 ),
    _attackDuration( 0 ) {
}

Json::Value CreatureCombat::toJson() {
    Json::Value values;
    values[ "attackCounter" ] = _attackCounter;
    values[ "attackDuration" ] = _attackDuration;
    return values;
}

double CreatureCombat::attack() const {
    return _attack;
}

void CreatureCombat::setAttack( double attack ) {
    _attack = attack;
}

double CreatureCombat::defense() const {
    return _defense;
}

void CreatureCombat::setDefense( double defense ) {
    _defense = defense;
}

int CreatureCombat::attackCounter() const {
    return _attackCounter;
}

void CreatureCombat::setAttackCounter( int attackCounter ) {
    _attackCounter = attackCounter;
}

int CreatureCombat::attackDuration() const {
    return _attackDuration;
}

void CreatureCombat::setAttackDuration( int attackDuration ) {
    _attackDuration = attackDuration;
}

} // namespace Domain
