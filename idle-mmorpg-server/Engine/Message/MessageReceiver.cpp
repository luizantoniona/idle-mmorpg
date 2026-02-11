#include "MessageReceiver.h"

#include <iostream>

#include <Engine/Instance/Stage/StageInstance.h>
#include <Engine/Instance/World/WorldInstance.h>
#include <Manager/World/WorldManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

#include "MessageHelper.h"

namespace Engine {

MessageReceiver::MessageReceiver() {}

void MessageReceiver::receive( const std::string& sessionId, const std::string& message ) {
    if ( message.empty() ) {
        return;
    }

    Json::Value root = Helper::JsonHelper::parseJsonString( message );
    if ( root.isNull() || !root.isObject() ) {
        return;
    }

    Engine::WorldInstance* worldInstance = Commons::Singleton<Manager::WorldManager>::instance().worldInstance();

    if ( !worldInstance ) {
        return;
    }

    Engine::StageInstance* stageInstance = worldInstance->characterStageInstance( sessionId );

    if ( !stageInstance ) {
        return;
    }

    std::cout << "Message received from: " << sessionId << " Message: " << message << std::endl;

    MessageReceiverType type = MessageHelper::stringToType( root[ "type" ].asString() );
    Json::Value payload = root[ "payload" ];
    switch ( type ) {
        case MessageReceiverType::COMBAT_ROOM_CREATE:
        case MessageReceiverType::COMBAT_ROOM_ENTER:
        case MessageReceiverType::COMBAT_ROOM_EXIT:
        case MessageReceiverType::CHARACTER_EQUIP_ITEM:
        case MessageReceiverType::CHARACTER_USE_ITEM:
        case MessageReceiverType::CHARACTER_CAST_SPELL:
        case MessageReceiverType::CHARACTER_ACTION_UPDATE:
            stageInstance->handleCharacterMessage( sessionId, type, payload );
            break;

            // case MessageReceiverType::CHARACTER_LOCATION_UPDATE:
            //     worldInstance->handleCharacterMessage( sessionId, type, payload );
            //     break;

        default:
            break;
    }
}

} // namespace Engine
