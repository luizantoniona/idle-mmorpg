#include "NotificationSystem.h"

#include <Commons/LocationHelper.h>
#include <Core/Message/MessageSender.h>

namespace Core::System {

void NotificationSystem::notifyFullCharacter( const std::string& sessionId, Model::Character* character ) {
    Json::Value characterJson = character->toJson();
    characterJson[ "action" ] = character->action().toJson();
    characterJson[ "attributes" ] = character->attributes().toJson();
    characterJson[ "combatAttributes" ] = character->combatAttributes().toJson();
    characterJson[ "coordinates" ] = character->coordinates().toJson();
    characterJson[ "inventory" ] = character->inventory().toJson();
    characterJson[ "equipment" ] = character->equipment().toJson();
    characterJson[ "progression" ] = character->progression().toJson();
    characterJson[ "quests" ] = character->quests().toJson();
    characterJson[ "skills" ] = character->skills().toJson();
    characterJson[ "vitals" ] = character->vitals().toJson();
    characterJson[ "wallet" ] = character->wallet().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_UPDATE, characterJson );
}

void NotificationSystem::notifyDeadCharacter( const std::string& sessionId ) {
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_DEAD, "" );
}

void NotificationSystem::notifyCharacterAttributes( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "attributes" ] = character->attributes().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_ATTRIBUTES_UPDATE, payload );
}

void NotificationSystem::notifyCharacterCombatAttributes( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "combatAttributes" ] = character->combatAttributes().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_COMBAT_ATTRIBUTES_UPDATE, payload );
}

void NotificationSystem::notifyCharacterInventory( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "inventory" ] = character->inventory().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_INVENTORY_UPDATE, payload );
}

void NotificationSystem::notifyCharacterProgression( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "progression" ] = character->progression().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_PROGRESSION_UPDATE, payload );
}

void NotificationSystem::notifyCharacterQuests( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "quests" ] = character->quests().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_QUESTS_UPDATE, payload );
}

void NotificationSystem::notifyCharacterSkills( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "skills" ] = character->skills().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_SKILLS_UPDATE, payload );
}

void NotificationSystem::notifyCharacterVitals( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "vitals" ] = character->vitals().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_VITALS_UPDATE, payload );
}

void NotificationSystem::notifyCharacterWallet( const std::string& sessionId, Model::Character* character ) {
    Json::Value payload;
    payload[ "wallet" ] = character->wallet().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_WALLET_UPDATE, payload );
}

void NotificationSystem::notifyCurrentAction( const std::string& sessionId, Model::Character* character ) {
    Json::Value payloadCurrentAction;
    payloadCurrentAction[ "action" ] = character->action().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_CURRENT_ACTION_UPDATE, payloadCurrentAction );
}

void NotificationSystem::notifyCurrentCoordinates( const std::string& sessionId, Model::Character* character ) {
    Json::Value payloadCurrentCoordinates;
    payloadCurrentCoordinates[ "coordinates" ] = character->coordinates().toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::CHARACTER_CURRENT_COORDINATES_UPDATE, payloadCurrentCoordinates );
}

void NotificationSystem::notifyFullLocation( const std::string& sessionId, const Model::Location* location ) {
    Json::Value payloadLocation;
    payloadLocation[ "location" ] = location->toJson();
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::LOCATION_UPDATE, payloadLocation );
}

void NotificationSystem::notifyLocationActions( const std::string& sessionId, Model::Character* character, const Model::Location* location ) {
    Json::Value payloadLocationActions;
    Json::Value availableActions;

    for ( auto action : location->actions() ) {
        if ( Commons::LocationHelper::canCharacterPerformAction( character, action ) ) {
            availableActions.append( action.toJson() );
        }
    }

    payloadLocationActions[ "actions" ] = availableActions;
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::LOCATION_ACTIONS_UPDATE, payloadLocationActions );
}

void NotificationSystem::notifyLocationConnections( const std::string& sessionId, Model::Character* character, const Model::Location* location ) {
    Json::Value payloadLocationConnections;
    Json::Value availableConnections;

    for ( auto connection : location->connections() ) {
        if ( Commons::LocationHelper::canCharacterUseConnections( character, connection ) ) {
            availableConnections.append( connection.toJson() );
        }
    }

    payloadLocationConnections[ "connections" ] = availableConnections;
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::LOCATION_CONNECTIONS_UPDATE, payloadLocationConnections );
}

void NotificationSystem::notifyLocationDenizens( const std::string& sessionId, Model::Character* character, const Model::Location* location ) {
    Json::Value payloadLocationDenizens;
    Json::Value availableDenizens;

    for ( auto denizen : location->denizens() ) {
        if ( Commons::LocationHelper::canCharacterInteractDenizen( character, denizen ) ) {
            Json::Value denizenJson = denizen.toJson();

            Json::Value availableQuests;
            for ( const auto& quest : denizen.quests() ) {
                if ( Commons::LocationHelper::canCharacterSeeDenizenQuest( character, quest ) ) {
                    availableQuests.append( quest.toJson() );
                }
            }

            denizenJson[ "quests" ] = availableQuests;
            availableDenizens.append( denizenJson );
        }
    }

    payloadLocationDenizens[ "denizens" ] = availableDenizens;
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::LOCATION_DENIZENS_UPDATE, payloadLocationDenizens );
}

void NotificationSystem::notifyCombatInstances( const std::string& sessionId, std::vector<Instance::CombatInstance*> combatInstances ) {
    Json::Value payloadCombatInstances;
    Json::Value combatArray;

    for ( const auto* combat : combatInstances ) {
        combatArray.append( combat->instanceToJson() );
    }

    payloadCombatInstances["combatInstances"] = combatArray;
    Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::COMBAT_ROOMS_UPDATE, payloadCombatInstances );
}

void NotificationSystem::notifyCombat( const Core::Instance::CombatInstance* combatInstance ) {
    Json::Value payloadCombatInstance;
    payloadCombatInstance["combat"] = combatInstance->combatToJson();

    for ( const auto& [sessionId, character] : combatInstance->characters() ) {
        Core::Message::MessageSender::send( sessionId, Message::MessageSenderType::COMBAT_UPDATE, payloadCombatInstance );
    }
}

} // namespace Core::System
