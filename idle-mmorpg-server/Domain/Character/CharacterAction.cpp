#include "CharacterAction.h"

namespace Domain {

CharacterAction::CharacterAction() :
    _type( ActionType::UNKNOWN ),
    _action( nullptr ) {
}

Json::Value CharacterAction::toJson() const {
    Json::Value values;
    if ( _action ) {
        values[ "type" ] = static_cast<int>( _action->type() );
        values[ "description" ] = _action->description();
    }
    return values;
}

ActionType CharacterAction::type() const {
    return _type;
}

void CharacterAction::setType( ActionType type ) {
    _type = type;
}

Action* CharacterAction::action() const {
    return _action;
}

void CharacterAction::setAction( Action* action ) {
    _action = action;
}

} // namespace Domain
