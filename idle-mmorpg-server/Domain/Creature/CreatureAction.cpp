#include "CreatureAction.h"

namespace Domain {

CreatureAction::CreatureAction() :
    _duration( 0 ),
    _counter( 0 ) {
}

Json::Value CreatureAction::toJson() {
    Json::Value root;
    root[ "duration" ] = duration();
    root[ "counter" ] = counter();
    return root;
}

int CreatureAction::duration() const {
    return _duration;
}

void CreatureAction::setDuration( int duration ) {
    _duration = duration;
}

int CreatureAction::counter() const {
    return _counter;
}

void CreatureAction::setCounter( int counter ) {
    _counter = counter;
}

} // namespace Domain
