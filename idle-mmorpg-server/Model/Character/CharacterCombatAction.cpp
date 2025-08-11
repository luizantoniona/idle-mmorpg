#include "CharacterCombatAction.h"

namespace {
constexpr const char* JSON_DURATION = "duration";
constexpr const char* JSON_COUNTER = "counter";
} // namespace

namespace Model {

CharacterCombatAction::CharacterCombatAction() :
    _duration( 0 ),
    _counter( 0 ),
    _regenDuration( 20 ),
    _regenCounter( 0 ) {
}

Json::Value CharacterCombatAction::toJson() {
    Json::Value root;
    root[ JSON_DURATION ] = duration();
    root[ JSON_COUNTER ] = counter();
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

int CharacterCombatAction::regenDuration() const {
    return _regenDuration;
}

void CharacterCombatAction::setRegenDuration( int regenDuration ) {
    _regenDuration = regenDuration;
}

int CharacterCombatAction::regenCounter() const {
    return _regenCounter;
}

void CharacterCombatAction::setRegenCounter( int regenCounter ) {
    _regenCounter = regenCounter;
}

} // namespace Model
