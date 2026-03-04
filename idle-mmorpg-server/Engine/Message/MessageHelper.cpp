#include "MessageHelper.h"

#include <unordered_map>

namespace Engine {

MessageReceiverType MessageHelper::stringToType( const std::string& type ) {
    static const std::unordered_map<std::string, MessageReceiverType> map = {
        { "CHARACTER_SET_ACTION", MessageReceiverType::CHARACTER_SET_ACTION },

        { "COMBAT_ROOM_CREATE", MessageReceiverType::COMBAT_ROOM_CREATE },
        { "COMBAT_ROOM_ENTER", MessageReceiverType::COMBAT_ROOM_ENTER },
        { "COMBAT_ROOM_EXIT", MessageReceiverType::COMBAT_ROOM_EXIT },

        // REVIEW
        { "CHARACTER_EQUIP_ITEM", MessageReceiverType::CHARACTER_EQUIP_ITEM },
        { "CHARACTER_USE_ITEM", MessageReceiverType::CHARACTER_USE_ITEM },
        { "CHARACTER_CAST_SPELL", MessageReceiverType::CHARACTER_CAST_SPELL },
    };

    auto it = map.find( type );
    return it != map.end() ? it->second : MessageReceiverType::UNKNOWN;
}

std::string MessageHelper::typeToString( const MessageSenderType type ) {
    switch ( type ) {

        // --- Character Updates ---
    case MessageSenderType::CHARACTER:
        return "CHARACTER";
    case MessageSenderType::CHARACTER_ACTIONS:
        return "CHARACTER_ACTIONS";
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

        // --- Combat Rooms Updates ---
    case MessageSenderType::COMBAT_ROOMS:
        return "COMBAT_ROOMS";

        // --- Combat Updates ---
    case MessageSenderType::COMBAT:
        return "COMBAT";

    default:
        return "UNKNOWN";
    }
}

} // namespace Engine
