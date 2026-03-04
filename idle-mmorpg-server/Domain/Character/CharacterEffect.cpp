#include "CharacterEffect.h"

namespace Domain {

CharacterEffect::CharacterEffect() :
    _source( "" ),
    _sourceName( "" ),
    _type( "" ),
    _category( "" ),
    _value( 0.0 ),
    _duration( 0 ),
    _counter( 0 ) {}

Json::Value Domain::CharacterEffect::toJson() {
    Json::Value values;
    values[ "source" ] = source();
    values[ "sourceName" ] = sourceName();
    values[ "type" ] = type();
    values[ "category" ] = category();
    values[ "value" ] = value();
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

std::string CharacterEffect::type() const {
    return _type;
}

void CharacterEffect::setType( const std::string& type ) {
    _type = type;
}

std::string CharacterEffect::category() const {
    return _category;
}

void CharacterEffect::setCategory( const std::string& category ) {
    _category = category;
}

double CharacterEffect::value() const {
    return _value;
}

void CharacterEffect::setValue( double value ) {
    _value = value;
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
