#include "MessageHelper.h"

#include <unordered_map>

namespace Core::Message {

MessageReceiverType MessageHelper::stringToType( const std::string& type ) {
    static const std::unordered_map<std::string, MessageReceiverType> map = {
        { "CHARACTER_ACTION_UPDATE", MessageReceiverType::CHARACTER_ACTION_UPDATE },
        { "CHARACTER_STRUCTURE_UPDATE", MessageReceiverType::CHARACTER_STRUCTURE_UPDATE },
        { "CHARACTER_LOCATION_UPDATE", MessageReceiverType::CHARACTER_LOCATION_UPDATE },

        { "COMBAT_ROOM_CREATE", MessageReceiverType::COMBAT_ROOM_CREATE },
        { "COMBAT_ROOM_ENTER", MessageReceiverType::COMBAT_ROOM_ENTER },
        { "COMBAT_ROOM_EXIT", MessageReceiverType::COMBAT_ROOM_EXIT },
    };

    auto it = map.find( type );
    return it != map.end() ? it->second : MessageReceiverType::UNKNOWN;
}

std::string MessageHelper::typeToString( const MessageSenderType type ) {
    switch ( type ) {
        case MessageSenderType::CHARACTER_UPDATE:
            return "CHARACTER_UPDATE";
        case MessageSenderType::CHARACTER_DEAD:
            return "CHARACTER_DEAD";
        case MessageSenderType::CHARACTER_ATTRIBUTES_UPDATE:
            return "CHARACTER_ATTRIBUTES_UPDATE";
        case MessageSenderType::CHARACTER_COMBAT_ATTRIBUTES_UPDATE:
            return "CHARACTER_COMBAT_ATTRIBUTES_UPDATE";
        case MessageSenderType::CHARACTER_EQUIPMENT_UPDATE:
            return "CHARACTER_EQUIPMENT_UPDATE";
        case MessageSenderType::CHARACTER_INVENTORY_UPDATE:
            return "CHARACTER_INVENTORY_UPDATE";
        case MessageSenderType::CHARACTER_PROGRESSION_UPDATE:
            return "CHARACTER_PROGRESSION_UPDATE";
        case MessageSenderType::CHARACTER_SKILLS_UPDATE:
            return "CHARACTER_SKILLS_UPDATE";
        case MessageSenderType::CHARACTER_VITALS_UPDATE:
            return "CHARACTER_VITALS_UPDATE";
        case MessageSenderType::CHARACTER_WALLET_UPDATE:
            return "CHARACTER_WALLET_UPDATE";

        case MessageSenderType::CHARACTER_CURRENT_ACTION_UPDATE:
            return "CHARACTER_CURRENT_ACTION_UPDATE";
        case MessageSenderType::CHARACTER_CURRENT_COORDINATES_UPDATE:
            return "CHARACTER_CURRENT_COORDINATES_UPDATE";

        case MessageSenderType::LOCATION_UPDATE:
            return "LOCATION_UPDATE";
        case MessageSenderType::LOCATION_ACTIONS_UPDATE:
            return "LOCATION_ACTIONS_UPDATE";
        case MessageSenderType::LOCATION_CONNECTIONS_UPDATE:
            return "LOCATION_CONNECTIONS_UPDATE";

        case MessageSenderType::COMBAT_ROOMS_UPDATE:
            return "COMBAT_ROOMS_UPDATE";
        case MessageSenderType::COMBAT_UPDATE:
            return "COMBAT_UPDATE";

        default:
            return "UNKNOWN";
    }
}

} // namespace Core::Message
