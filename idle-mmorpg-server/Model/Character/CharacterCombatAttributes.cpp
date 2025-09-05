#include "CharacterCombatAttributes.h"

namespace Model {

CharacterCombatAttributes::CharacterCombatAttributes() :
    _attack( 0.0 ),
    _attackSpeed( 1.0 ),
    _defense( 0.0 ) {}

double CharacterCombatAttributes::attack() const {
    return _attack;
}

void CharacterCombatAttributes::setAttack( double attack ) {
    _attack = attack;
}

double CharacterCombatAttributes::attackSpeed() const {
    return _attackSpeed;
}

void CharacterCombatAttributes::setAttackSpeed( double attackSpeed ) {
    _attackSpeed = attackSpeed;
}

double CharacterCombatAttributes::defense() const {
    return _defense;
}

void CharacterCombatAttributes::setDefense( double defense ) {
    _defense = defense;
}

void CharacterCombatAttributes::clear() {
    _attack = 0.0;
    _defense = 0.0;
    _attackSpeed = 1.0;
}

} // namespace Model
