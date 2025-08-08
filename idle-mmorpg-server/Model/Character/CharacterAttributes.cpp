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

    root[ "strength" ] = Strength();
    root[ "dexterity" ] = Dexterity();
    root[ "constitution" ] = Constitution();
    root[ "intelligence" ] = Intelligence();
    root[ "wisdom" ] = Wisdom();

    root[ "baseStrength" ] = _baseStrength;
    root[ "baseDexterity" ] = _baseDexterity;
    root[ "baseConstitution" ] = _baseConstitution;
    root[ "baseIntelligence" ] = _baseIntelligence;
    root[ "baseWisdom" ] = _baseWisdom;

    root[ "modifierStrength" ] = _modifierStrength;
    root[ "modifierDexterity" ] = _modifierDexterity;
    root[ "modifierConstitution" ] = _modifierConstitution;
    root[ "modifierIntelligence" ] = _modifierIntelligence;
    root[ "modifierWisdom" ] = _modifierWisdom;

    return root;
}

double CharacterAttributes::Strength() const {
    return _baseStrength + _modifierStrength;
}

double CharacterAttributes::Dexterity() const {
    return _baseDexterity + _modifierDexterity;
}

double CharacterAttributes::Constitution() const {
    return _baseConstitution + _modifierConstitution;
}

double CharacterAttributes::Intelligence() const {
    return _baseIntelligence + _modifierIntelligence;
}

double CharacterAttributes::Wisdom() const {
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

} // namespace Model
