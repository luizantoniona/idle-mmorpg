#ifndef MESSAGESENDERTYPE_H
#define MESSAGESENDERTYPE_H

namespace Engine {

enum class MessageSenderType {
    UNKNOWN,

    // --- Character Updates ---
    CHARACTER,
    CHARACTER_ACTION,
    CHARACTER_EFFECTS,
    CHARACTER_EQUIPMENT,
    CHARACTER_INVENTORY,
    CHARACTER_PROGRESSION,
    CHARACTER_SKILLS,
    CHARACTER_SPELLS,
    CHARACTER_STAGE,
    CHARACTER_VITALS,
    CHARACTER_WALLET,

    // --- Stage Updates ---
    STAGE,

    // --- Combat Updates ---
    COMBAT,
    COMBAT_ROOMS,

    // --- OLD: Need Review

    CHARACTER_CURRENT_ACTION_UPDATE,
    CHARACTER_CURRENT_COORDINATES_UPDATE,
};

} // namespace Engine

#endif // MESSAGESENDERTYPE_H
