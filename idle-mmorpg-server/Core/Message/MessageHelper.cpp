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
        case MessageSenderType::CHARACTER_UPDATE:
            return "character_update";
        case MessageSenderType::CHARACTER_UPDATE_ATTRIBUTES:
            return "character_update_attributes";
        case MessageSenderType::CHARACTER_UPDATE_INVENTORY:
            return "character_update_inventory";
        case MessageSenderType::CHARACTER_UPDATE_PROGRESSION:
            return "character_update_progression";
        case MessageSenderType::CHARACTER_UPDATE_SKILLS:
            return "character_update_skills";
        case MessageSenderType::CHARACTER_UPDATE_VITALS:
            return "character_update_vitals";
        case MessageSenderType::CHARACTER_UPDATE_WALLET:
            return "character_update_wallet";

        case MessageSenderType::CHARACTER_UPDATE_ACTION:
            return "character_update_action";

        case MessageSenderType::LOCATION_UPDATE_POSITION:
            return "location_update_position";
        case MessageSenderType::LOCATION_UPDATE_ACTIONS:
            return "location_update_actions";
        default:
            return "unknown";
    }
}

} // namespace Core::Message
