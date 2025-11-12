#include "CreatureCombatAction.h"

namespace {
constexpr const char* JSON_DURATION = "duration";
constexpr const char* JSON_COUNTER = "counter";
} // namespace

namespace Domain {

CreatureCombatAction::CreatureCombatAction() :
    _duration( 0 ),
    _counter( 0 ) {
}

Json::Value CreatureCombatAction::toJson() {
    Json::Value root;
    root[ JSON_DURATION ] = duration();
    root[ JSON_COUNTER ] = counter();
    return root;
}

int CreatureCombatAction::duration() const {
    return _duration;
}

void CreatureCombatAction::setDuration( int duration ) {
    _duration = duration;
}

int CreatureCombatAction::counter() const {
    return _counter;
}

void CreatureCombatAction::setCounter( int counter ) {
    _counter = counter;
}

} // namespace Domain
