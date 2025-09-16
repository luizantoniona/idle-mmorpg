#include "CharacterEffect.h"

namespace Model {

CharacterEffect::CharacterEffect() :
    _id( "" ),
    _type( "" ),
    _category( "" ),
    _value( 0.0 ),
    _duration( 0 ),
    _counter( 0 ) {
}

Json::Value Model::CharacterEffect::toJson() {
    Json::Value root;
    return root;
}

std::string CharacterEffect::id() const {
    return _id;
}

void CharacterEffect::setId( const std::string& id ) {
    _id = id;
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

} // namespace Model
