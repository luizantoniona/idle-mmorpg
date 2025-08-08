#include "CharacterCombatAttributes.h"

namespace Model {

CharacterCombatAttributes::CharacterCombatAttributes() :
    _baseAttack( 0.0 ),
    _baseAccuracy( 0.0 ),
    _baseDefense( 0.0 ),
    _baseSpeed( 0.0 ),
    _baseEvasion( 0.0 ),
    _baseCriticalChance( 0.0 ),
    _baseCriticalMultiplier( 1.0 ),
    _modifierAttack( 0.0 ),
    _modifierAccuracy( 0.0 ),
    _modifierDefense( 0.0 ),
    _modifierSpeed( 0.0 ),
    _modifierEvasion( 0.0 ),
    _modifierCriticalChance( 0.0 ),
    _modifierCriticalMultiplier( 0.0 ) {
}

Json::Value CharacterCombatAttributes::toJson() const {
    Json::Value root;
    root[ "attack" ] = _baseAttack;
    root[ "accuracy" ] = _baseAccuracy;
    root[ "defense" ] = _baseDefense;
    root[ "speed" ] = _baseSpeed;
    root[ "evasion" ] = _baseEvasion;
    root[ "criticalChance" ] = _baseCriticalChance;
    root[ "criticalMultiplier" ] = _baseCriticalMultiplier;

    root[ "modifierAttack" ] = _modifierAttack;
    root[ "modifierAccuracy" ] = _modifierAccuracy;
    root[ "modifierDefense" ] = _modifierDefense;
    root[ "modifierSpeed" ] = _modifierSpeed;
    root[ "modifierEvasion" ] = _modifierEvasion;
    root[ "modifierCriticalChance" ] = _modifierCriticalChance;
    root[ "modifierCriticalMultiplier" ] = _modifierCriticalMultiplier;

    return root;
}

double CharacterCombatAttributes::attack() const {
    return _baseAttack + _modifierAttack;
}

double CharacterCombatAttributes::accuracy() const {
    return _baseAccuracy + _modifierAccuracy;
}

double CharacterCombatAttributes::defense() const {
    return _baseDefense + _modifierDefense;
}

double CharacterCombatAttributes::speed() const {
    return _baseSpeed + _modifierSpeed;
}

double CharacterCombatAttributes::evasion() const {
    return _baseEvasion + _modifierEvasion;
}

double CharacterCombatAttributes::criticalChance() const {
    return _baseCriticalChance + _modifierCriticalChance;
}

double CharacterCombatAttributes::criticalMultiplier() const {
    return _baseCriticalMultiplier + _modifierCriticalMultiplier;
}

double CharacterCombatAttributes::baseAttack() const {
    return _baseAttack;
}

void CharacterCombatAttributes::setBaseAttack( double baseAttack ) {
    _baseAttack = baseAttack;
}

double CharacterCombatAttributes::baseAccuracy() const {
    return _baseAccuracy;
}

void CharacterCombatAttributes::setBaseAccuracy( double baseAccuracy ) {
    _baseAccuracy = baseAccuracy;
}

double CharacterCombatAttributes::baseDefense() const {
    return _baseDefense;
}

void CharacterCombatAttributes::setBaseDefense( double baseDefense ) {
    _baseDefense = baseDefense;
}

double CharacterCombatAttributes::baseSpeed() const {
    return _baseSpeed;
}

void CharacterCombatAttributes::setBaseSpeed( double baseSpeed ) {
    _baseSpeed = baseSpeed;
}

double CharacterCombatAttributes::baseEvasion() const {
    return _baseEvasion;
}

void CharacterCombatAttributes::setBaseEvasion( double baseEvasion ) {
    _baseEvasion = baseEvasion;
}

double CharacterCombatAttributes::baseCriticalChance() const {
    return _baseCriticalChance;
}

void CharacterCombatAttributes::setBaseCriticalChance( double baseCriticalChance ) {
    _baseCriticalChance = baseCriticalChance;
}

double CharacterCombatAttributes::baseCriticalMultiplier() const {
    return _baseCriticalMultiplier;
}

void CharacterCombatAttributes::setBaseCriticalMultiplier( double baseCriticalMultiplier ) {
    _baseCriticalMultiplier = baseCriticalMultiplier;
}

void CharacterCombatAttributes::modifyAttack( double modifier ) {
    _modifierAttack += modifier;
}

void CharacterCombatAttributes::modifyAccuracy( double modifier ) {
    _modifierAccuracy += modifier;
}

void CharacterCombatAttributes::modifyDefense( double modifier ) {
    _modifierDefense += modifier;
}

void CharacterCombatAttributes::modifySpeed( double modifier ) {
    _modifierSpeed += modifier;
}

void CharacterCombatAttributes::modifyEvasion( double modifier ) {
    _modifierEvasion += modifier;
}

void CharacterCombatAttributes::modifyCriticalChance( double modifier ) {
    _modifierCriticalChance += modifier;
}

void CharacterCombatAttributes::modifyCriticalMultiplier( double modifier ) {
    _modifierCriticalMultiplier += modifier;
}

} // namespace Model
