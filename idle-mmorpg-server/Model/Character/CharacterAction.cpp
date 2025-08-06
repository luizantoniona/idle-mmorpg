#include "CharacterAction.h"

namespace {
constexpr const char* JSON_ID = "id";
constexpr const char* JSON_DURATION = "duration";
constexpr const char* JSON_COUNTER = "counter";
} // namespace

namespace Model {

CharacterAction::CharacterAction() :
    _id( "idle" ),
    _duration( 0 ),
    _counter( 0 ) {
}

Json::Value CharacterAction::toJson() {
    Json::Value root;
    root[ JSON_ID ] = id();
    root[ JSON_DURATION ] = duration();
    root[ JSON_COUNTER ] = counter();

    return root;
}

std::string CharacterAction::id() const {
    return _id;
}

void CharacterAction::setId( const std::string& id ) {
    _id = id;
}

int CharacterAction::duration() const {
    return _duration;
}

void CharacterAction::setDuration( int duration ) {
    _duration = duration;
}

int CharacterAction::counter() const {
    return _counter;
}

void CharacterAction::setCounter( int counter ) {
    _counter = counter;
}

void CharacterAction::clear() {
    setId( "idle" );
    setDuration( 0 );
    setCounter( 0 );
}

} // namespace Model
