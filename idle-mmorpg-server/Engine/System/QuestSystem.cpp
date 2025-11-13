#include "QuestSystem.h"

#include <iostream>

#include <Domain/World/Location/LocationHelper.h>
#include <Engine/Manager/Quest/QuestManager.h>
#include <Shared/Commons/Singleton.h>

#include "LootSystem.h"
#include "NotificationSystem.h"
#include "SpellSystem.h"

namespace Engine {

void QuestSystem::characterAcceptQuest( const std::string& sessionId, Domain::Character* character, const Domain::Location* location, const Json::Value& payload ) {
    const std::string denizenId = payload[ "denizenId" ].asString();

    bool found = false;
    Domain::Denizen* denizenToAccept;
    for ( auto& denizen : location->denizens() ) {
        if ( denizenId == denizen->id() && Helper::LocationHelper::canCharacterInteractDenizen( character, *denizen ) ) {
            denizenToAccept = denizen;
            found = true;
            break;
        }
    }

    if ( !found ) {
        return;
    }

    const std::string questId = payload[ "questId" ].asString();
    if ( !denizenToAccept->hasQuestById( questId ) ) {
        return;
    }

    Domain::CharacterQuests& characterQuests = character->quests();
    if ( characterQuests.isQuestProceeding( questId ) || characterQuests.isQuestFinished( questId ) ) {
        return;
    }

    const Domain::Quest* quest = Commons::Singleton<Engine::QuestManager>::instance().questById( questId );
    if ( !quest ) {
        return;
    }

    if ( quest->type() == "talk" && quest->objectiveId() == denizenId ) {
        Domain::CharacterQuest questToAdd;
        questToAdd.setId( questId );
        questToAdd.setType( quest->type() );
        questToAdd.setObjectiveId( quest->objectiveId() );
        questToAdd.setCurrentAmount( quest->amount() );
        questToAdd.setObjectiveAmount( quest->amount() );
        questToAdd.setFinished( true );
        questToAdd.setQuest( quest );

        characterQuests.addProceeding( questToAdd );

    } else {
        Domain::CharacterQuest questToAdd;
        questToAdd.setId( questId );
        questToAdd.setType( quest->type() );
        questToAdd.setObjectiveId( quest->objectiveId() );
        questToAdd.setCurrentAmount( 0 );
        questToAdd.setObjectiveAmount( quest->amount() );
        questToAdd.setFinished( false );
        questToAdd.setQuest( quest );

        characterQuests.addProceeding( questToAdd );

        updateItemQuest( sessionId, character );
    }

    NotificationSystem::notifyCharacterQuests( sessionId, character );
    NotificationSystem::notifyLocationDenizens( sessionId, character, location );
}

void QuestSystem::characterFinishQuest( const std::string& sessionId, Domain::Character* character, const Domain::Location* location, const Json::Value& payload ) {
    const std::string denizenId = payload[ "denizenId" ].asString();

    bool found = false;
    Domain::Denizen* denizenToFinish;
    for ( auto& denizen : location->denizens() ) {
        if ( denizenId == denizen->id() && Helper::LocationHelper::canCharacterInteractDenizen( character, *denizen ) ) {
            denizenToFinish = denizen;
            found = true;
            break;
        }
    }

    if ( !found ) {
        return;
    }

    const std::string questId = payload[ "questId" ].asString();
    if ( !denizenToFinish->hasQuestById( questId ) ) {
        return;
    }

    Domain::CharacterQuests& characterQuests = character->quests();
    if ( !characterQuests.isQuestProceeding( questId ) ) {
        return;
    }

    if ( !characterQuests.isQuestObjectiveCompleted( questId ) ) {
        return;
    }

    if ( auto* quest = characterQuests.findQuestProceeding( questId ) ) {
        quest->setFinished( true );

        if ( quest->quest() ) {
            const Domain::Quest* baseQuest = quest->quest();

            if ( baseQuest->type() == "item" ) {
                character->inventory().removeItem( baseQuest->objectiveId(), baseQuest->amount() );
                NotificationSystem::notifyCharacterInventory( sessionId, character );
            }

            for ( auto& reward : baseQuest->rewards() ) {
                if ( reward.type() == "item" ) {
                    Engine::LootSystem::addItem( sessionId, character, reward.id(), reward.amount() );

                } else if ( reward.type() == "spell" ) {
                    Engine::SpellSystem::learnSpell( sessionId, character, reward.id() );

                } else {
                    std::cerr << "QuestSystem::characterFinishQuest Unknow reward type: " << reward.type() << std::endl;
                }
            }
        }

        characterQuests.moveQuestToFinished( questId );
    }

    NotificationSystem::notifyCharacterQuests( sessionId, character );
    NotificationSystem::notifyLocationConnections( sessionId, character, location );
    NotificationSystem::notifyLocationDenizens( sessionId, character, location );
}

void QuestSystem::updateKillQuest( const std::string& sessionId, Domain::Character* character, const std::string& creatureId ) {
    for ( auto& quest : character->quests().proceeding() ) {

        if ( quest.type() == "kill" && !quest.finished() ) {
            if ( quest.objectiveId() == creatureId ) {
                quest.setCurrentAmount( quest.currentAmount() + 1 );

                if ( quest.currentAmount() >= quest.objectiveAmount() ) {
                    quest.setFinished( true );
                }

                NotificationSystem::notifyCharacterQuests( sessionId, character );
            }
        }
    }
}

void QuestSystem::updateItemQuest( const std::string& sessionId, Domain::Character* character ) {
    for ( auto& quest : character->quests().proceeding() ) {
        if ( quest.type() == "item" ) {
            int count = 0;

            for ( const auto& item : character->inventory().items() ) {
                if ( item.id() == quest.objectiveId() ) {
                    count += item.amount();
                }
            }

            int oldAmount = quest.currentAmount();
            bool oldFinished = quest.finished();

            quest.setCurrentAmount( count );
            quest.setFinished( count >= quest.objectiveAmount() );

            if ( quest.currentAmount() != oldAmount || quest.finished() != oldFinished ) {
                NotificationSystem::notifyCharacterQuests( sessionId, character );
            }
        }
    }
}

void QuestSystem::updateTalkQuest( const std::string& sessionId, Domain::Character* character, const std::string& denizenId ) {
    for ( auto& quest : character->quests().proceeding() ) {

        if ( quest.type() == "talk" && !quest.finished() ) {

            if ( quest.objectiveId() == denizenId ) {
                quest.setCurrentAmount( 1 );
                quest.setFinished( true );
                NotificationSystem::notifyCharacterQuests( sessionId, character );
            }
        }
    }
}

} // namespace Engine
