#include "CharacterCombatAction.h"

namespace Domain {

CharacterCombatAction::CharacterCombatAction() :
    _duration( 0 ),
    _counter( 0 ) {}

Json::Value CharacterCombatAction::toJson() {
    Json::Value root;
    root[ "duration" ] = duration();
    root[ "counter" ] = counter();
    return root;
}

int CharacterCombatAction::duration() const {
    return _duration;
}

void CharacterCombatAction::setDuration( int duration ) {
    _duration = duration;
}

int CharacterCombatAction::counter() const {
    return _counter;
}

void CharacterCombatAction::setCounter( int counter ) {
    _counter = counter;
}

} // namespace Domain
