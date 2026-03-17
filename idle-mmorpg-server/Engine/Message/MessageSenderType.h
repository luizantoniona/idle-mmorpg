#ifndef MESSAGESENDERTYPE_H
#define MESSAGESENDERTYPE_H

namespace Engine {

enum class MessageSenderType {
    // --- Character Updates ---
    CHARACTER,
    CHARACTER_ACTIONS,
    CHARACTER_COMBAT,
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

    // --- Combat Rooms Updates ---
    COMBAT_ROOMS,

    // --- Combat ---
    COMBAT,

    UNKNOWN,
};

} // namespace Engine

#endif // MESSAGESENDERTYPE_H
