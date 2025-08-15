#include "MessageReceiver.h"

#include <iostream>

#include <Commons/JsonHelper.h>
#include <Commons/Singleton.h>
#include <Core/Instance/LocationInstance.h>
#include <Core/Instance/RegionInstance.h>
#include <Core/Instance/WorldInstance.h>
#include <Core/Manager/WorldManager.h>

#include "MessageHelper.h"

namespace Core::Message {

MessageReceiver::MessageReceiver() {}

void MessageReceiver::receive( const std::string& sessionId, const std::string& message ) {

    if ( message.empty() ) {
        return;
    }

    Core::Instance::WorldInstance* worldInstance = Commons::Singleton<Core::Manager::WorldManager>::instance().worldInstance();

    if ( !worldInstance ) {
        return;
    }

    Core::Instance::RegionInstance* regionInstance = worldInstance->characterRegionInstance( sessionId );

    if ( !regionInstance ) {
        return;
    }

    Core::Instance::LocationInstance* locationInstance = worldInstance->characterLocationInstance( sessionId );

    if ( !locationInstance ) {
        return;
    }

    std::cout << "Message received from: " << sessionId << " Message: " << message << std::endl;

    Json::Value root = Commons::JsonHelper::parseJsonString( message );
    if ( root.isNull() || !root.isObject() ) {
        return;
    }

    MessageReceiverType type = MessageHelper::stringToType( root[ "type" ].asString() );
    Json::Value payload = root[ "payload" ];
    switch ( type ) {
    case MessageReceiverType::COMBAT_ROOM_CREATE:
    case MessageReceiverType::COMBAT_ROOM_ENTER:
    case MessageReceiverType::COMBAT_ROOM_EXIT:
    case MessageReceiverType::CHARACTER_TRADE_DENIZEN:
    case MessageReceiverType::CHARACTER_ACCEPT_DENIZEN_QUEST:
    case MessageReceiverType::CHARACTER_FINISH_DENIZEN_QUEST:
    case MessageReceiverType::CHARACTER_STRUCTURE_UPDATE:
    case MessageReceiverType::CHARACTER_ACTION_UPDATE:
        locationInstance->handleCharacterMessage( sessionId, type, payload );
        break;

    case MessageReceiverType::CHARACTER_LOCATION_UPDATE:
        regionInstance->handleCharacterMessage( sessionId, type, payload );
        break;

    default:
        break;
    }
}

} // namespace Core::Message
