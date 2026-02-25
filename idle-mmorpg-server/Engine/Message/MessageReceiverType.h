#ifndef MESSAGERECEIVERTYPE_H
#define MESSAGERECEIVERTYPE_H

namespace Engine {

enum class MessageReceiverType {
    UNKNOWN,

    // --- Character Updates ---
    CHARACTER_SET_ACTION,

    // --- OLD: Need Review
    CHARACTER_EQUIP_ITEM,
    CHARACTER_USE_ITEM,
    CHARACTER_CAST_SPELL,

    COMBAT_ROOM_CREATE,
    COMBAT_ROOM_ENTER,
    COMBAT_ROOM_EXIT,
};

} // namespace Engine

#endif // MESSAGERECEIVERTYPE_H
