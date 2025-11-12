#ifndef CHARACTERQUESTS_H
#define CHARACTERQUESTS_H

#include <vector>

#include <json/json.h>

#include "CharacterQuest.h"

namespace Domain {

class CharacterQuests {
public:
    CharacterQuests();

    Json::Value toJson();

    std::vector<CharacterQuest>& proceeding();
    void setProceeding( const std::vector<CharacterQuest>& proceeding );
    void addProceeding( const CharacterQuest& proceeding );

    std::vector<CharacterQuest>& finished();
    void setFinished( const std::vector<CharacterQuest>& finished );
    void addFinished( const CharacterQuest& finished );

    bool isQuestProceeding( const std::string& questId ) const;
    bool isQuestFinished( const std::string& questId ) const;
    bool isQuestObjectiveCompleted( const std::string& questId ) const;
    CharacterQuest* findQuestProceeding( const std::string& questId );
    void moveQuestToFinished( const std::string& questId );

private:
    std::vector<CharacterQuest> _proceeding;
    std::vector<CharacterQuest> _finished;
};

} // namespace Domain

#endif // CHARACTERQUESTS_H
