#include "CharacterAttributes.h"

namespace Model {

CharacterAttributes::CharacterAttributes() :
    _strength( 0.0 ),
    _dexterity( 0.0 ),
    _constitution( 0.0 ),
    _intelligence( 0.0 ),
    _wisdom( 0.0 ) {
}

Json::Value CharacterAttributes::toJson() const {
    Json::Value root;
    root[ "strength" ] = strength();
    root[ "dexterity" ] = dexterity();
    root[ "constitution" ] = constitution();
    root[ "intelligence" ] = intelligence();
    root[ "wisdom" ] = wisdom();
    return root;
}

double CharacterAttributes::strength() const {
    return _strength;
}

void CharacterAttributes::setStrength( double strength ) {
    _strength = strength;
}

double CharacterAttributes::dexterity() const {
    return _dexterity;
}

void CharacterAttributes::setDexterity( double dexterity ) {
    _dexterity = dexterity;
}

double CharacterAttributes::constitution() const {
    return _constitution;
}

void CharacterAttributes::setConstitution( double constitution ) {
    _constitution = constitution;
}

double CharacterAttributes::intelligence() const {
    return _intelligence;
}

void CharacterAttributes::setIntelligence( double intelligence ) {
    _intelligence = intelligence;
}

double CharacterAttributes::wisdom() const {
    return _wisdom;
}

void CharacterAttributes::setWisdom( double wisdom ) {
    _wisdom = wisdom;
}

} // namespace Model
