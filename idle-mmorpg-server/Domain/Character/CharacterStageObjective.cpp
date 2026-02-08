#include "CharacterStageObjective.h"

namespace Domain {

CharacterStageObjective::CharacterStageObjective() :
    _currentAmount( 0 ),
    _completed( false ) {
}

const std::string& CharacterStageObjective::idObjective() const {
    return _idObjective;
}

void CharacterStageObjective::setIdObjective( const std::string& idObjective ) {
    _idObjective = idObjective;
}

int CharacterStageObjective::currentAmount() const {
    return _currentAmount;
}

void CharacterStageObjective::setCurrentAmount( int currentAmount ) {
    _currentAmount = currentAmount;
}

bool CharacterStageObjective::completed() const {
    return _completed;
}

void CharacterStageObjective::setCompleted( bool completed ) {
    _completed = completed;
}

} // namespace Domain
