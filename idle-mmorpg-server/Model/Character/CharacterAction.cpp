#include "CharacterAction.h"

namespace Model {

CharacterAction::CharacterAction() :
    _idAction( "idle" ),
    _duration( 0 ),
    _counter( 0 ) {
}

std::string CharacterAction::idAction() const {
    return _idAction;
}

void CharacterAction::setIdAction( const std::string& idAction ) {
    _idAction = idAction;
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

} // namespace Model
