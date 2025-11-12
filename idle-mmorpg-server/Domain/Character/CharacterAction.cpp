#include "CharacterAction.h"

namespace Domain {

CharacterAction::CharacterAction() :
    _id( "idle" ),
    _duration( 0 ),
    _counter( 0 ) {}

Json::Value CharacterAction::toJson() {
    Json::Value root;
    root[ "id" ] = id();
    root[ "duration" ] = duration();
    root[ "counter" ] = counter();

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

} // namespace Domain
