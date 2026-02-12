#include "CharacterActions.h"

namespace Domain {

CharacterActions::CharacterActions() :
    _id( "idle" ),
    _duration( 0 ),
    _counter( 0 ) {}

Json::Value CharacterActions::toJson() {
    Json::Value root;
    root[ "id" ] = id();
    root[ "duration" ] = duration();
    root[ "counter" ] = counter();

    return root;
}

std::string CharacterActions::id() const {
    return _id;
}

void CharacterActions::setId( const std::string& id ) {
    _id = id;
}

int CharacterActions::duration() const {
    return _duration;
}

void CharacterActions::setDuration( int duration ) {
    _duration = duration;
}

int CharacterActions::counter() const {
    return _counter;
}

void CharacterActions::setCounter( int counter ) {
    _counter = counter;
}

void CharacterActions::clear() {
    setId( "idle" );
    setDuration( 0 );
    setCounter( 0 );
}

} // namespace Domain
