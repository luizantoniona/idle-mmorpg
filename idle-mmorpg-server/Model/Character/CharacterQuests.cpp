#include "CharacterQuests.h"

namespace Model {

CharacterQuests::CharacterQuests() {
}

std::vector<CharacterQuest>& CharacterQuests::inProgress() {
    return _inProgress;
}

void CharacterQuests::setInProgress( const std::vector<CharacterQuest>& inProgress ) {
    _inProgress = inProgress;
}

void CharacterQuests::addInProgress( const CharacterQuest& inProgress ) {
    _inProgress.push_back( inProgress );
}

std::vector<CharacterQuest>& CharacterQuests::finished() {
    return _finished;
}

void CharacterQuests::setFinished( const std::vector<CharacterQuest>& finished ) {
    _finished = finished;
}

void CharacterQuests::addFinished( const CharacterQuest& finished ) {
    _finished.push_back( finished );
}

bool CharacterQuests::isQuestInProgress( const std::string& questId ) const {
    for ( const auto& quest : _inProgress ) {
        if ( quest.id() == questId ) {
            return true;
        }
    }

    return false;
}

bool CharacterQuests::isQuestFinished( const std::string& questId ) const {
    for ( const auto& quest : _finished ) {
        if ( quest.id() == questId ) {
            return true;
        }
    }

    return false;
}

bool CharacterQuests::isQuestObjectiveCompleted( const std::string& questId ) const {
    for ( const auto& quest : _inProgress ) {
        if ( quest.id() == questId ) {
            return quest.finished();
        }
    }

    return false;
}

CharacterQuest* CharacterQuests::findQuestInProgress( const std::string& questId ) {
    for ( auto& quest : _inProgress ) {
        if ( quest.id() == questId )
            return &quest;
    }

    return nullptr;
}

} // namespace Model
