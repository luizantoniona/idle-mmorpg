#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include <string>
#include <unordered_map>

#include <Model/Quest/Quest.h>

namespace Core::Manager {

class QuestManager {
public:
    QuestManager();

    void addQuest( std::unique_ptr<Model::Quest> quest );

    const Model::Quest* questById( const std::string& idQuest ) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Model::Quest>> _quests;
};

} // namespace Core::Manager

#endif // QUESTMANAGER_H
