#include "CharacterCombatAttributes.h"

namespace Model {

CharacterCombatAttributes::CharacterCombatAttributes() :
    _attack( 0.0 ),
    _defense( 0.0 ),
    _attackSpeed( 1.0 ),
    _criticalChance( 0.0 ),
    _criticalMultiplier( 1.0 ) {
}

double CharacterCombatAttributes::attack() const {
    return _attack;
}

void CharacterCombatAttributes::setAttack( double attack ) {
    _attack = attack;
}

double CharacterCombatAttributes::defense() const {
    return _defense;
}

void CharacterCombatAttributes::setDefense( double defense ) {
    _defense = defense;
}

double CharacterCombatAttributes::attackSpeed() const {
    return _attackSpeed;
}

void CharacterCombatAttributes::setAttackSpeed( double attackSpeed ) {
    _attackSpeed = attackSpeed;
}

double CharacterCombatAttributes::criticalChance() const {
    return _criticalChance;
}

void CharacterCombatAttributes::setCriticalChance( double criticalChance ) {
    _criticalChance = criticalChance;
}

double CharacterCombatAttributes::criticalMultiplier() const {
    return _criticalMultiplier;
}

void CharacterCombatAttributes::setCriticalMultiplier( double criticalMultiplier ) {
    _criticalMultiplier = criticalMultiplier;
}

void CharacterCombatAttributes::clear() {
    _attack = 0.0;
    _defense = 0.0;
    _attackSpeed = 1.0;
    _criticalChance = 0.0;
    _criticalMultiplier = 1.0;
}

} // namespace Model
