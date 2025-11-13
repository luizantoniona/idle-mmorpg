#include "NotificationSystem.h"

#include <Domain/World/Location/LocationHelper.h>
#include <Engine/Message/MessageSender.h>

namespace Engine {

void NotificationSystem::notifyFullCharacter( const std::string& sessionId, Domain::Character* character ) {
    Json::Value characterJson = character->toJson();
    characterJson[ "action" ] = character->action().toJson();
    characterJson[ "coordinates" ] = character->coordinates().toJson();
    characterJson[ "inventory" ] = character->inventory().toJson();
    characterJson[ "equipment" ] = character->equipment().toJson();
    characterJson[ "effects" ] = character->effects().toJson();
    characterJson[ "progression" ] = character->progression().toJson();
    characterJson[ "quests" ] = character->quests().toJson();
    characterJson[ "skills" ] = character->skills().toJson();
    characterJson[ "spells" ] = character->spells().toJson();
    characterJson[ "vitals" ] = character->vitals().toJson();
    characterJson[ "wallet" ] = character->wallet().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_UPDATE, characterJson );
}

void NotificationSystem::notifyDeadCharacter( const std::string& sessionId ) {
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_DEAD, "" );
}

void NotificationSystem::notifyCharacterAttributes( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "combatAttributes" ] = character->combatAttributes().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_ATTRIBUTES_UPDATE, payload );
}

void NotificationSystem::notifyCharacterEffects( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "effects" ] = character->effects().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_EFFECTS_UPDATE, payload );
}

void NotificationSystem::notifyCharacterEquipment( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "equipment" ] = character->equipment().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_EQUIPMENT_UPDATE, payload );
}

void NotificationSystem::notifyCharacterInventory( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "inventory" ] = character->inventory().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_INVENTORY_UPDATE, payload );
}

void NotificationSystem::notifyCharacterProgression( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "progression" ] = character->progression().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_PROGRESSION_UPDATE, payload );
}

void NotificationSystem::notifyCharacterQuests( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "quests" ] = character->quests().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_QUESTS_UPDATE, payload );
}

void NotificationSystem::notifyCharacterSkills( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "skills" ] = character->skills().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_SKILLS_UPDATE, payload );
}

void NotificationSystem::notifyCharacterSpells( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "spells" ] = character->spells().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_SPELLS_UPDATE, payload );
}

void NotificationSystem::notifyCharacterVitals( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "vitals" ] = character->vitals().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_VITALS_UPDATE, payload );
}

void NotificationSystem::notifyCharacterWallet( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payload;
    payload[ "wallet" ] = character->wallet().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_WALLET_UPDATE, payload );
}

void NotificationSystem::notifyCurrentAction( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payloadCurrentAction;
    payloadCurrentAction[ "action" ] = character->action().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_CURRENT_ACTION_UPDATE, payloadCurrentAction );
}

void NotificationSystem::notifyCurrentCoordinates( const std::string& sessionId, Domain::Character* character ) {
    Json::Value payloadCurrentCoordinates;
    payloadCurrentCoordinates[ "coordinates" ] = character->coordinates().toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::CHARACTER_CURRENT_COORDINATES_UPDATE, payloadCurrentCoordinates );
}

void NotificationSystem::notifyFullLocation( const std::string& sessionId, const Domain::Location* location ) {
    Json::Value payloadLocation;
    payloadLocation[ "location" ] = location->toJson();
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::LOCATION_UPDATE, payloadLocation );
}

void NotificationSystem::notifyLocationActions( const std::string& sessionId, Domain::Character* character, const Domain::Location* location ) {
    Json::Value payloadLocationActions;
    Json::Value availableActions;

    for ( auto action : location->actions() ) {
        if ( Helper::LocationHelper::canCharacterPerformAction( character, action ) ) {
            availableActions.append( action.toJson() );
        }
    }

    payloadLocationActions[ "actions" ] = availableActions;
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::LOCATION_ACTIONS_UPDATE, payloadLocationActions );
}

void NotificationSystem::notifyLocationConnections( const std::string& sessionId, Domain::Character* character, const Domain::Location* location ) {
    Json::Value payloadLocationConnections;
    Json::Value availableConnections;

    for ( auto connection : location->connections() ) {
        if ( Helper::LocationHelper::canCharacterUseConnections( character, connection ) ) {
            availableConnections.append( connection.toJson() );
        }
    }

    payloadLocationConnections[ "connections" ] = availableConnections;
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::LOCATION_CONNECTIONS_UPDATE, payloadLocationConnections );
}

void NotificationSystem::notifyLocationDenizens( const std::string& sessionId, Domain::Character* character, const Domain::Location* location ) {
    Json::Value payloadLocationDenizens;
    Json::Value availableDenizens;

    for ( auto denizen : location->denizens() ) {
        if ( Helper::LocationHelper::canCharacterInteractDenizen( character, *denizen ) ) {
            Json::Value denizenJson = denizen->toJson();

            Json::Value availableQuests;
            for ( const auto& quest : denizen->quests() ) {
                if ( Helper::LocationHelper::canCharacterSeeDenizenQuest( character, quest ) ) {
                    availableQuests.append( quest.toJson() );
                }
            }

            denizenJson[ "quests" ] = availableQuests;
            availableDenizens.append( denizenJson );
        }
    }

    payloadLocationDenizens[ "denizens" ] = availableDenizens;
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::LOCATION_DENIZENS_UPDATE, payloadLocationDenizens );
}

void NotificationSystem::notifyCombatInstances( const std::string& sessionId, std::vector<Engine::CombatInstance*> combatInstances ) {
    Json::Value payloadCombatInstances;
    Json::Value combatArray;

    for ( const auto* combat : combatInstances ) {
        combatArray.append( combat->instanceToJson() );
    }

    payloadCombatInstances[ "combatInstances" ] = combatArray;
    Engine::MessageSender::send( sessionId, Engine::MessageSenderType::COMBAT_ROOMS_UPDATE, payloadCombatInstances );
}

void NotificationSystem::notifyCombat( const Engine::CombatInstance* combatInstance ) {
    Json::Value payloadCombatInstance;
    payloadCombatInstance[ "combat" ] = combatInstance->combatToJson();

    for ( const auto& [ sessionId, character ] : combatInstance->characters() ) {
        Engine::MessageSender::send( sessionId, Engine::MessageSenderType::COMBAT_UPDATE, payloadCombatInstance );
    }
}

} // namespace Engine
