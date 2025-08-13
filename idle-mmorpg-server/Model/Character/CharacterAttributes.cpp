#include "CharacterAttributes.h"

namespace {
constexpr const char* JSON_STRENGTH = "strength";
constexpr const char* JSON_MODIFIER_STRENGTH = "modifierStrength";
constexpr const char* JSON_DEXTERITY = "dexterity";
constexpr const char* JSON_MODIFIER_DEXTERITY = "modifierDexterity";
constexpr const char* JSON_CONSTITUTION = "constitution";
constexpr const char* JSON_MODIFIER_CONSTITUTION = "modifierConstitution";
constexpr const char* JSON_INTELLIGENCE = "intelligence";
constexpr const char* JSON_MODIFIER_INTELLIGENCE = "modifierIntelligence";
constexpr const char* JSON_WISDOM = "wisdom";
constexpr const char* JSON_MODIFIER_WISDOM = "modifierWisdom";
} // namespace

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
    _modifierWisdom( 0.0 ) {}

Json::Value CharacterAttributes::toJson() const {
    Json::Value root;
    root[ JSON_STRENGTH ] = _baseStrength;
    root[ JSON_MODIFIER_STRENGTH ] = _modifierStrength;
    root[ JSON_DEXTERITY ] = _baseDexterity;
    root[ JSON_MODIFIER_DEXTERITY ] = _modifierDexterity;
    root[ JSON_CONSTITUTION ] = _baseConstitution;
    root[ JSON_MODIFIER_CONSTITUTION ] = _modifierConstitution;
    root[ JSON_INTELLIGENCE ] = _baseIntelligence;
    root[ JSON_MODIFIER_INTELLIGENCE ] = _modifierIntelligence;
    root[ JSON_WISDOM ] = _baseWisdom;
    root[ JSON_MODIFIER_WISDOM ] = _modifierWisdom;
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

} // namespace Model
