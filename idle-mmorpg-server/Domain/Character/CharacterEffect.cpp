#include "CharacterEffect.h"

namespace Domain {

CharacterEffect::CharacterEffect() :
    _source( "" ),
    _sourceName( "" ),
    _health( 0.0 ),
    _mana( 0.0 ),
    _stamina( 0.0 ),
    _duration( 0 ),
    _counter( 0 ) {}

Json::Value Domain::CharacterEffect::toJson() {
    Json::Value values;
    values[ "source" ] = source();
    values[ "sourceName" ] = sourceName();
    values[ "health" ] = _health;
    values[ "mana" ] = _mana;
    values[ "stamina" ] = _stamina;
    values[ "duration" ] = duration();
    values[ "counter" ] = counter();
    return values;
}

std::string CharacterEffect::source() const {
    return _source;
}

void CharacterEffect::setSource( const std::string& source ) {
    _source = source;
}

std::string CharacterEffect::sourceName() const {
    return _sourceName;
}

void CharacterEffect::setSourceName( const std::string& sourceName ) {
    _sourceName = sourceName;
}

double CharacterEffect::health() const {
    return _health;
}

void CharacterEffect::setHealth( double health ) {
    _health = health;
}

double CharacterEffect::mana() const {
    return _mana;
}

void CharacterEffect::setMana( double mana ) {
    _mana = mana;
}

double CharacterEffect::stamina() const {
    return _stamina;
}

void CharacterEffect::setStamina( double stamina ) {
    _stamina = stamina;
}

int CharacterEffect::duration() const {
    return _duration;
}

void CharacterEffect::setDuration( int duration ) {
    _duration = duration;
}

int CharacterEffect::counter() const {
    return _counter;
}

void CharacterEffect::setCounter( int counter ) {
    _counter = counter;
}

} // namespace Domain
