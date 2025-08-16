#include "CharacterQuests.h"

namespace Model {

CharacterQuests::CharacterQuests() {
}

Json::Value CharacterQuests::toJson() {
    Json::Value root;

    Json::Value proceedingJson;
    for ( auto& quest : _proceeding ) {
        proceedingJson.append( quest.toJson() );
    }
    root[ "proceeding" ] = proceedingJson;

    Json::Value finishedJson;
    for ( auto& quest : _finished ) {
        finishedJson.append( quest.toJson() );
    }
    root[ "finished" ] = finishedJson;

    return root;
}

std::vector<CharacterQuest>& CharacterQuests::proceeding() {
    return _proceeding;
}

void CharacterQuests::setProceeding( const std::vector<CharacterQuest>& proceeding ) {
    _proceeding = proceeding;
}

void CharacterQuests::addProceeding( const CharacterQuest& proceeding ) {
    _proceeding.push_back( proceeding );
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

bool CharacterQuests::isQuestProceeding( const std::string& questId ) const {
    for ( const auto& quest : _proceeding ) {
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
    for ( const auto& quest : _proceeding ) {
        if ( quest.id() == questId ) {
            return quest.finished();
        }
    }

    return false;
}

CharacterQuest* CharacterQuests::findQuestProceeding( const std::string& questId ) {
    for ( auto& quest : _proceeding ) {
        if ( quest.id() == questId )
            return &quest;
    }

    return nullptr;
}

void CharacterQuests::moveQuestToFinished( const std::string& questId ) {
    for ( auto it = _proceeding.begin(); it != _proceeding.end(); ++it ) {

        if ( it->id() == questId ) {
            _finished.push_back( std::move( *it ) );
            _proceeding.erase( it );
            return;
        }
    }
}

} // namespace Model
