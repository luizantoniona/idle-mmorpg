#ifndef CHARACTERQUESTS_H
#define CHARACTERQUESTS_H

#include <vector>

#include "CharacterQuest.h"

namespace Model {

class CharacterQuests {
public:
    CharacterQuests();

    std::vector<CharacterQuest>& inProgress();
    void setInProgress( const std::vector<CharacterQuest>& inProgress );
    void addInProgress( const CharacterQuest& inProgress );

    std::vector<CharacterQuest>& finished();
    void setFinished( const std::vector<CharacterQuest>& finished );
    void addFinished( const CharacterQuest& finished );

    bool isQuestInProgress( const std::string& questId ) const;
    bool isQuestFinished( const std::string& questId ) const;
    bool isQuestObjectiveCompleted( const std::string& questId ) const;
    CharacterQuest* findQuestInProgress( const std::string& questId );

private:
    std::vector<CharacterQuest> _inProgress;
    std::vector<CharacterQuest> _finished;
};

} // namespace Model

#endif // CHARACTERQUESTS_H
