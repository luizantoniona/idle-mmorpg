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
        case MessageReceiverType::CHARACTER_UPDATE_STRUCTURE:
        case MessageReceiverType::CHARACTER_UPDATE_ACTION: {
            locationInstance->handleCharacterMessage( sessionId, type, payload );
            break;
        }
        default:
            break;
    }
}

} // namespace Core::Message
