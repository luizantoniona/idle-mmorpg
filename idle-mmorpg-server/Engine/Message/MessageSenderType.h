#ifndef MESSAGESENDERTYPE_H
#define MESSAGESENDERTYPE_H

namespace Engine {

enum class MessageSenderType {
    UNKNOWN,

    // --- Character Updates ---
    CHARACTER,
    CHARACTER_ACTIONS,
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
};

} // namespace Engine

#endif // MESSAGESENDERTYPE_H
