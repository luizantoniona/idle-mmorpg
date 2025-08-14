#include "CharacterQuest.h"

namespace Model {

CharacterQuest::CharacterQuest() {
}

std::string CharacterQuest::id() const {
    return _id;
}

void CharacterQuest::setId( const std::string& id ) {
    _id = id;
}

std::string CharacterQuest::type() const {
    return _type;
}

void CharacterQuest::setType( const std::string& type ) {
    _type = type;
}

std::string CharacterQuest::objectiveId() const {
    return _objectiveId;
}

void CharacterQuest::setObjectiveId( const std::string& objectiveId ) {
    _objectiveId = objectiveId;
}

int CharacterQuest::currentAmount() const {
    return _currentAmount;
}

void CharacterQuest::setCurrentAmount( int currentAmount ) {
    _currentAmount = currentAmount;
}

int CharacterQuest::objectiveAmount() const {
    return _objectiveAmount;
}

void CharacterQuest::setObjectiveAmount( int objectiveAmount ) {
    _objectiveAmount = objectiveAmount;
}

bool CharacterQuest::finished() const {
    return _finished;
}

void CharacterQuest::setFinished( bool finished ) {
    _finished = finished;
}

} // namespace Model
