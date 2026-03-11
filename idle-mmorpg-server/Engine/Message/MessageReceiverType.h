#ifndef MESSAGERECEIVERTYPE_H
#define MESSAGERECEIVERTYPE_H

namespace Engine {

enum class MessageReceiverType {
    UNKNOWN,

    // --- Character Updates ---
    CHARACTER_ACTION_SET,
    CHARACTER_ITEM_EQUIP,
    CHARACTER_ITEM_USE,

    // --- Combat Rooms Updates ---
    COMBAT_ROOM_CREATE,
    COMBAT_ROOM_ENTER,
    COMBAT_ROOM_EXIT,

    // --- OLD: Need Review
    CHARACTER_CAST_SPELL,
};

} // namespace Engine

#endif // MESSAGERECEIVERTYPE_H
