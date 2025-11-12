#include "QuestManager.h"

namespace Engine {

QuestManager::QuestManager() {}

void QuestManager::addQuest( std::unique_ptr<Domain::Quest> quest ) {
    std::string id = quest->id();
    _quests[ id ] = std::move( quest );
}

const Domain::Quest* QuestManager::questById( const std::string& idQuest ) const {
    auto it = _quests.find( idQuest );
    if ( it != _quests.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Engine
