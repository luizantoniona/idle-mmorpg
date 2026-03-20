#include "CharacterActions.h"

namespace Domain {

CharacterActions::CharacterActions() :
    _currentAction(),
    _actions(),
    _duration( 0 ),
    _counter( 0 ) {
}

Json::Value CharacterActions::toJson() const {
    Json::Value values;
    values[ "duration" ] = duration();
    values[ "counter" ] = counter();
    values[ "currentAction" ] = _currentAction.toJson();
    for ( const auto& action : _actions ) {
        values[ "availableActions" ].append( action.toJson() );
    }

    Json::Value actions;
    actions[ "actions" ] = values;

    return actions;
}

CharacterAction CharacterActions::currentAction() const {
    return _currentAction;
}

void CharacterActions::setCurrentAction( CharacterAction currentAction ) {
    _currentAction = currentAction;
}

std::vector<CharacterAction>& CharacterActions::actions() {
    return _actions;
}

void CharacterActions::setActions( const std::vector<CharacterAction>& actions ) {
    _actions = actions;
}

void CharacterActions::addAction( const CharacterAction& action ) {
    _actions.push_back( action );
}

void CharacterActions::clearActions() {
    _actions.clear();
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

} // namespace Domain
