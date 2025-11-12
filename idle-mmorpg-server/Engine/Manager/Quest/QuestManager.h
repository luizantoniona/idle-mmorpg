#ifndef QUESTMANAGER_H
#define QUESTMANAGER_H

#include <string>
#include <unordered_map>

#include <Domain/Quest/Quest.h>

namespace Engine {

class QuestManager {
public:
    QuestManager();

    void addQuest( std::unique_ptr<Domain::Quest> quest );

    const Domain::Quest* questById( const std::string& idQuest ) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Domain::Quest> > _quests;
};

} // namespace Engine

#endif // QUESTMANAGER_H
