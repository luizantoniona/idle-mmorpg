#include "QuestSystem.h"

#include <Commons/LocationHelper.h>

#include "NotificationSystem.h"

namespace Core::System {

void QuestSystem::characterAcceptQuest( const std::string& sessionId, Model::Character* character, const Model::Location* location, const Json::Value& payload ) {
    const std::string denizenId = payload["denizenId"].asString();

    bool found = false;
    Model::Denizen denizenToTrade;
    for ( auto& denizen : location->denizens() ) {
        if ( denizenId == denizen.id() && Commons::LocationHelper::canCharacterInteractDenizen( character, denizen ) ) {
            denizenToTrade = denizen;
            found = true;
            break;
        }
    }

    if ( !found ) {
        return;
    }

    const std::string questId = payload["questId"].asString();

    // Verificar se denizem possui quest

    Model::CharacterQuests& quests = character->quests();

    //TODO Verificar se quest já está com personagem;
//    quests.finished();
//    quests.proceeding();

    // Se não estiver, adicionar ao character a nova
    // Criar a nova

    NotificationSystem::notifyCharacterQuests( sessionId, character );
}

void QuestSystem::characterFinishQuest( const std::string& sessionId, Model::Character* character, const Model::Location* location, const Json::Value& payload ) {
    const std::string denizenId = payload["denizenId"].asString();

    bool found = false;
    Model::Denizen denizenToTrade;
    for ( auto& denizen : location->denizens() ) {
        if ( denizenId == denizen.id() && Commons::LocationHelper::canCharacterInteractDenizen( character, denizen ) ) {
            denizenToTrade = denizen;
            found = true;
            break;
        }
    }

    if ( !found ) {
        return;
    }

    const std::string questId = payload["questId"].asString();

    // Verificar se denizem possui quest

    Model::CharacterQuests& quests = character->quests();

    //TODO Verificar se quest já está com personagem;
    //quests.proceeding();
    //validar requisitos para finalizar
    //finalizar quest
    //dar recompensa
    //

    NotificationSystem::notifyCharacterQuests( sessionId, character );
    NotificationSystem::notifyCharacterInventory( sessionId, character );
    NotificationSystem::notifyCharacterWallet( sessionId, character );
    NotificationSystem::notifyLocationDenizens( sessionId, character, location );

}

} // namespace Core::System
