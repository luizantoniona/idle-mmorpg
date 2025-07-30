#include "MessageHelper.h"

#include <unordered_map>

namespace Core::Message {

MessageReceiverType MessageHelper::stringToType( const std::string& type ) {
    static const std::unordered_map<std::string, MessageReceiverType> map = {
        { "character_update_action", MessageReceiverType::CHARACTER_UPDATE_ACTION },
    };

    auto it = map.find( type );
    return it != map.end() ? it->second : MessageReceiverType::UNKNOWN;
}

std::string MessageHelper::typeToString( const MessageSenderType type ) {
    switch ( type ) {
    case MessageSenderType::CHARACTER_UPDATE_ACTION:
        return "character_update_action";
    case MessageSenderType::CHARACTER_UPDATE_ATTRIBUTES:
        return "character_update_attributes";
    case MessageSenderType::CHARACTER_UPDATE_STATUS:
        return "character_update_status";
    case MessageSenderType::CHARACTER_UPDATE_INVENTORY:
        return "character_update_inventory";
    case MessageSenderType::CHARACTER_UPDATE_WALLET:
        return "character_update_wallet";

    case MessageSenderType::LOCATION_UPDATE_POSITION:
        return "location_update_position";
    case MessageSenderType::LOCATION_UPDATE_ACTIONS:
        return "location_update_actions";
    default:
        return "unknown";
    }
}

} // namespace Core::Message
