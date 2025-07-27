#include "CharacterAction.h"

namespace Model {

CharacterAction::CharacterAction() {
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

} // namespace Model
