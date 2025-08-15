#include "CharacterQuest.h"

namespace Model {

CharacterQuest::CharacterQuest() {
}

Json::Value CharacterQuest::toJson() {
    Json::Value root;
    root[ "id" ] = _id;
    root[ "type" ] = _type;
    root[ "currentAmount" ] = _currentAmount;
    root[ "objectiveAmount" ] = _objectiveAmount;
    root[ "finished" ] = _finished;

    if ( _quest ) {
        root[ "title" ] = _quest->title();
        root[ "description" ] = _quest->description();
    }

    return root;
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

const Quest* CharacterQuest::quest() const {
    return _quest;
}

void CharacterQuest::setQuest( const Quest* quest ) {
    _quest = quest;
}

} // namespace Model
