#include "MessageHelper.h"

#include <unordered_map>

namespace Engine {

MessageReceiverType MessageHelper::stringToType( const std::string& type ) {
    static const std::unordered_map<std::string, MessageReceiverType> map = {
        { "CHARACTER_ACTION_UPDATE", MessageReceiverType::CHARACTER_ACTION_UPDATE },

        { "CHARACTER_EQUIP_ITEM", MessageReceiverType::CHARACTER_EQUIP_ITEM },
        { "CHARACTER_USE_ITEM", MessageReceiverType::CHARACTER_USE_ITEM },
        { "CHARACTER_CAST_SPELL", MessageReceiverType::CHARACTER_CAST_SPELL },

        { "COMBAT_ROOM_CREATE", MessageReceiverType::COMBAT_ROOM_CREATE },
        { "COMBAT_ROOM_ENTER", MessageReceiverType::COMBAT_ROOM_ENTER },
        { "COMBAT_ROOM_EXIT", MessageReceiverType::COMBAT_ROOM_EXIT },
    };

    auto it = map.find( type );
    return it != map.end() ? it->second : MessageReceiverType::UNKNOWN;
}

std::string MessageHelper::typeToString( const MessageSenderType type ) {
    switch ( type ) {

        // --- Character Updates ---
    case MessageSenderType::CHARACTER:
        return "CHARACTER";
    case MessageSenderType::CHARACTER_ACTION:
        return "CHARACTER_ACTION";
    case MessageSenderType::CHARACTER_EFFECTS:
        return "CHARACTER_EFFECTS";
    case MessageSenderType::CHARACTER_EQUIPMENT:
        return "CHARACTER_EQUIPMENT";
    case MessageSenderType::CHARACTER_INVENTORY:
        return "CHARACTER_INVENTORY";
    case MessageSenderType::CHARACTER_PROGRESSION:
        return "CHARACTER_PROGRESSION";
    case MessageSenderType::CHARACTER_SKILLS:
        return "CHARACTER_SKILLS";
    case MessageSenderType::CHARACTER_SPELLS:
        return "CHARACTER_SPELLS";
    case MessageSenderType::CHARACTER_STAGE:
        return "CHARACTER_STAGE";
    case MessageSenderType::CHARACTER_VITALS:
        return "CHARACTER_VITALS";
    case MessageSenderType::CHARACTER_WALLET:
        return "CHARACTER_WALLET";

        // --- Stage Updates ---
    case MessageSenderType::STAGE:
        return "STAGE";

        // --- Combat Updates ---
    case MessageSenderType::COMBAT:
        return "COMBAT";
    case MessageSenderType::COMBAT_ROOMS:
        return "COMBAT_ROOMS";

        // --- OLD: Need Review
    case MessageSenderType::CHARACTER_CURRENT_ACTION_UPDATE:
        return "CHARACTER_CURRENT_ACTION_UPDATE";
    case MessageSenderType::CHARACTER_CURRENT_COORDINATES_UPDATE:
        return "CHARACTER_CURRENT_COORDINATES_UPDATE";

    default:
        return "UNKNOWN";
    }
}

} // namespace Engine
