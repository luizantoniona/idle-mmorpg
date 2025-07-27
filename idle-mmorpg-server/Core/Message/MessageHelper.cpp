#include "MessageHelper.h"

#include <unordered_map>

namespace System::Message {

MessageType MessageHelper::stringToType( const std::string& type ) {
    static const std::unordered_map<std::string, MessageType> map = {
        // Character RECEIVE related messages
        { "character_update_action", MessageType::CHARACTER_UPDATE_ACTION },

        // Location RECEIVE related messages
        { "location_update_position", MessageType::LOCATION_UPDATE_POSITION },
    };

    auto it = map.find( type );
    return it != map.end() ? it->second : MessageType::UNKNOWN;
}

std::string MessageHelper::typeToString( const MessageType type ) {
    switch ( type ) {
        // Character SEND related messages
    case MessageType::CHARACTER_UPDATE_ATTRIBUTES:
        return "character_update_attributes";
    case MessageType::CHARACTER_UPDATE_STATUS:
        return "character_update_status";
    case MessageType::CHARACTER_UPDATE_INVENTORY:
        return "character_update_inventory";
    case MessageType::CHARACTER_UPDATE_WALLET:
        return "character_update_wallet";

        // Location SEND related messages
    case MessageType::LOCATION_UPDATE_POSITION:
        return "location_update_position";
    case MessageType::LOCATION_UPDATE_ACTIONS:
        return "location_update_actions";
    default:
        return "unknown";
    }
}

} // namespace System::Message
