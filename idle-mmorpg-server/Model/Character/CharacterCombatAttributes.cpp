#include "CharacterCombatAttributes.h"

namespace Model {

CharacterCombatAttributes::CharacterCombatAttributes() :
    _attack( 0.0 ),
    _attackSpeed( 1.0 ),
    _defense( 0.0 ) {}

Json::Value CharacterCombatAttributes::toJson() const {
    Json::Value root;
    root[ "attack" ] = attack();
    root[ "attackSpeed" ] = attackSpeed();
    root[ "defense" ] = defense();
    return root;
}

double CharacterCombatAttributes::attack() const {
    return _attack;
}

void CharacterCombatAttributes::setAttack( double attack ) {
    _attack = attack;
}

void CharacterCombatAttributes::modifyAttack( double modifier ) {
    _attack += modifier;
}

double CharacterCombatAttributes::attackSpeed() const {
    return _attackSpeed;
}

void CharacterCombatAttributes::setAttackSpeed( double attackSpeed ) {
    _attackSpeed = attackSpeed;
}

void CharacterCombatAttributes::modifyAttackSpeed( double modifier ) {
    _attackSpeed += modifier;
}

double CharacterCombatAttributes::defense() const {
    return _defense;
}

void CharacterCombatAttributes::setDefense( double defense ) {
    _defense = defense;
}

void CharacterCombatAttributes::modifyDefense( double modifier ) {
    _defense += modifier;
}

void CharacterCombatAttributes::clear() {
    _attack = 0.0;
    _defense = 0.0;
    _attackSpeed = 1.0;
}

} // namespace Model
