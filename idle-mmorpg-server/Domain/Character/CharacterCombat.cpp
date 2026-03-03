#include "CharacterCombat.h"

namespace Domain {

CharacterCombat::CharacterCombat() :
    _isInCombat( false ),
    _attack( 0.00 ),
    _attackCounter( 0 ),
    _attackDuration( 0 ) {
}

Json::Value CharacterCombat::toJson() {
    Json::Value values;
    values[ "attackCounter" ] = _attackCounter;
    values[ "attackDuration" ] = _attackDuration;

    Json::Value combatJson;
    combatJson[ "combat" ] = values;
    return combatJson;
}

bool CharacterCombat::isInCombat() const {
    return _isInCombat;
}

void CharacterCombat::setIsInCombat( bool isInCombat ) {
    _isInCombat = isInCombat;
}

double CharacterCombat::attack() const {
    return _attack;
}

void CharacterCombat::setAttack( double attack ) {
    _attack = attack;
}

int CharacterCombat::attackCounter() const {
    return _attackCounter;
}

void CharacterCombat::setAttackCounter( int attackCounter ) {
    _attackCounter = attackCounter;
}

int CharacterCombat::attackDuration() const {
    return _attackDuration;
}

void CharacterCombat::setAttackDuration( int attackDuration ) {
    _attackDuration = attackDuration;
}

} // namespace Domain
