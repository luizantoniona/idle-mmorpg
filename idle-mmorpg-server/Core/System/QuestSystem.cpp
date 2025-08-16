#include "QuestSystem.h"

#include <iostream>

#include <Commons/LocationHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/QuestManager.h>

#include "LootSystem.h"
#include "NotificationSystem.h"
#include "SpellSystem.h"

namespace Core::System {

void QuestSystem::characterAcceptQuest( const std::string& sessionId, Model::Character* character, const Model::Location* location, const Json::Value& payload ) {
    const std::string denizenId = payload["denizenId"].asString();

    bool found = false;
    Model::Denizen denizenToAccept;
    for ( auto& denizen : location->denizens() ) {
        if ( denizenId == denizen.id() && Commons::LocationHelper::canCharacterInteractDenizen( character, denizen ) ) {
            denizenToAccept = denizen;
            found = true;
            break;
        }
    }

    if ( !found ) {
        return;
    }

    const std::string questId = payload["questId"].asString();
    if ( !denizenToAccept.hasQuestById( questId ) ) {
        return;
    }

    Model::CharacterQuests& characterQuests = character->quests();
    if ( characterQuests.isQuestProceeding( questId ) || characterQuests.isQuestFinished( questId ) ) {
        return;
    }

    const Model::Quest* quest = Commons::Singleton<Core::Manager::QuestManager>::instance().questById( questId );
    if ( !quest ) {
        return;
    }

    Model::CharacterQuest questToAdd;
    questToAdd.setId( questId );
    questToAdd.setType( quest->type() );
    questToAdd.setObjectiveId( quest->objectiveId() );
    questToAdd.setCurrentAmount( 0 );
    questToAdd.setObjectiveAmount( quest->amount() );
    questToAdd.setFinished( false );
    questToAdd.setQuest( quest );

    characterQuests.addProceeding( questToAdd );

    NotificationSystem::notifyCharacterQuests( sessionId, character );
    NotificationSystem::notifyLocationDenizens( sessionId, character, location );
}

void QuestSystem::characterFinishQuest( const std::string& sessionId, Model::Character* character, const Model::Location* location, const Json::Value& payload ) {
    const std::string denizenId = payload["denizenId"].asString();

    bool found = false;
    Model::Denizen denizenToFinish;
    for ( auto& denizen : location->denizens() ) {
        if ( denizenId == denizen.id() && Commons::LocationHelper::canCharacterInteractDenizen( character, denizen ) ) {
            denizenToFinish = denizen;
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
