#include "QuestManager.h"

namespace Core::Manager {

QuestManager::QuestManager() {
}

void QuestManager::addQuest( std::unique_ptr<Model::Quest> quest ) {
    std::string id = quest->id();
    _quests[ id ] = std::move( quest );
}

const Model::Quest* QuestManager::questById( const std::string& idQuest ) const {
    auto it = _quests.find( idQuest );
    if ( it != _quests.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Core::Manager
