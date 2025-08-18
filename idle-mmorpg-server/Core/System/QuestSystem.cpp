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

    if ( quest->type() == "talk" && quest->objectiveId() == denizenId ) {
        Model::CharacterQuest questToAdd;
        questToAdd.setId( questId );
        questToAdd.setType( quest->type() );
        questToAdd.setObjectiveId( quest->objectiveId() );
        questToAdd.setCurrentAmount( quest->amount() );
        questToAdd.setObjectiveAmount( quest->amount() );
        questToAdd.setFinished( true );
        questToAdd.setQuest( quest );

        characterQuests.addProceeding( questToAdd );

    } else {
        Model::CharacterQuest questToAdd;
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
    if ( !denizenToFinish.hasQuestById( questId ) ) {
        return;
    }

    Model::CharacterQuests& characterQuests = character->quests();
    if ( !characterQuests.isQuestProceeding( questId ) ) {
        return;
    }

    if ( !characterQuests.isQuestObjectiveCompleted( questId ) ) {
        return;
    }

    if ( auto* quest = characterQuests.findQuestProceeding( questId ) ) {
        quest->setFinished( true );

        if ( quest->quest() ) {
            const Model::Quest* baseQuest = quest->quest();

            if ( baseQuest->type() == "item" ) {
                character->inventory().removeItem( baseQuest->objectiveId(), baseQuest->amount() );
            }

            for ( auto& reward : baseQuest->rewards() ) {
                if ( reward.type() == "item" ) {
                    Core::System::LootSystem::addItem( sessionId, character, reward.id(), reward.amount() );

                } else if ( reward.type() == "spell" ) {
                    Core::System::SpellSystem::learnSpell( sessionId, character, reward.id() );

                } else {
                    std::cerr << "QuestSystem::characterFinishQuest Unknow reward type: " << reward.type() << std::endl;
                }
            }
        }

        characterQuests.moveQuestToFinished( questId );
    }

    NotificationSystem::notifyCharacterInventory( sessionId, character );
    NotificationSystem::notifyCharacterQuests( sessionId, character );
    NotificationSystem::notifyLocationDenizens( sessionId, character, location );
}

void QuestSystem::updateKillQuest( const std::string& sessionId, Model::Character* character, const std::string& creatureId ) {
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

void QuestSystem::updateItemQuest( const std::string& sessionId, Model::Character* character ) {
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

void QuestSystem::updateTalkQuest( const std::string& sessionId, Model::Character* character, const std::string& denizenId ) {
    for ( auto& quest : character->quests().proceeding() ) {

        if ( quest.type() == "talk" && !quest.finished() ) {

            if ( quest.objectiveId() == denizenId ) {
                quest.setFinished( true );
                NotificationSystem::notifyCharacterQuests( sessionId, character );
            }
        }
    }
}

} // namespace Core::System
