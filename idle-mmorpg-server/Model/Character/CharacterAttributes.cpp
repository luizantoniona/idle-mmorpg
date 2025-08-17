#include "CharacterAttributes.h"

namespace Model {

CharacterAttributes::CharacterAttributes() :
    _baseStrength( 0.0 ),
    _baseDexterity( 0.0 ),
    _baseConstitution( 0.0 ),
    _baseIntelligence( 0.0 ),
    _baseWisdom( 0.0 ),
    _modifierStrength( 0.0 ),
    _modifierDexterity( 0.0 ),
    _modifierConstitution( 0.0 ),
    _modifierIntelligence( 0.0 ),
    _modifierWisdom( 0.0 ) {
}

Json::Value CharacterAttributes::toJson() const {
    Json::Value root;
    root[ "strength" ] = _baseStrength;
    root[ "modifierStrength" ] = _modifierStrength;
    root[ "dexterity" ] = _baseDexterity;
    root[ "modifierDexterity" ] = _modifierDexterity;
    root[ "constitution" ] = _baseConstitution;
    root[ "modifierConstitution" ] = _modifierConstitution;
    root[ "intelligence" ] = _baseIntelligence;
    root[ "modifierIntelligence" ] = _modifierIntelligence;
    root[ "wisdom" ] = _baseWisdom;
    root[ "modifierWisdom" ] = _modifierWisdom;
    return root;
}

double CharacterAttributes::strength() const {
    return _baseStrength + _modifierStrength;
}

double CharacterAttributes::dexterity() const {
    return _baseDexterity + _modifierDexterity;
}

double CharacterAttributes::constitution() const {
    return _baseConstitution + _modifierConstitution;
}

double CharacterAttributes::intelligence() const {
    return _baseIntelligence + _modifierIntelligence;
}

double CharacterAttributes::wisdom() const {
    return _baseWisdom + _modifierWisdom;
}

double CharacterAttributes::baseStrength() const {
    return _baseStrength;
}

void CharacterAttributes::setBaseStrength( double baseStrength ) {
    _baseStrength = baseStrength;
}

double CharacterAttributes::baseDexterity() const {
    return _baseDexterity;
}

void CharacterAttributes::setBaseDexterity( double baseDexterity ) {
    _baseDexterity = baseDexterity;
}

double CharacterAttributes::baseConstitution() const {
    return _baseConstitution;
}

void CharacterAttributes::setBaseConstitution( double baseConstitution ) {
    _baseConstitution = baseConstitution;
}

double CharacterAttributes::baseIntelligence() const {
    return _baseIntelligence;
}

void CharacterAttributes::setBaseIntelligence( double baseIntelligence ) {
    _baseIntelligence = baseIntelligence;
}

double CharacterAttributes::baseWisdom() const {
    return _baseWisdom;
}

void CharacterAttributes::setBaseWisdom( double baseWisdom ) {
    _baseWisdom = baseWisdom;
}

void CharacterAttributes::modifyStrength( double modifier ) {
    _modifierStrength += modifier;
}

void CharacterAttributes::modifyDexterity( double modifier ) {
    _modifierDexterity += modifier;
}

void CharacterAttributes::modifyConstitution( double modifier ) {
    _modifierConstitution += modifier;
}

void CharacterAttributes::modifyIntelligence( double modifier ) {
    _modifierIntelligence += modifier;
}

void CharacterAttributes::modifyWisdom( double modifier ) {
    _modifierWisdom += modifier;
}

void CharacterAttributes::resetModifiers() {
    _modifierStrength = 0;
    _modifierDexterity = 0;
    _modifierConstitution = 0;
    _modifierIntelligence = 0;
    _modifierWisdom = 0;
}

} // namespace Model
