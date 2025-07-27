#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

namespace System::Message {

enum class MessageType {
    UNKNOWN,

    // Character related messages
    CHARACTER_UPDATE_ATTRIBUTES, // SEND
    CHARACTER_UPDATE_STATUS,     // SEND
    CHARACTER_UPDATE_SKILLS,     // SEND
    CHARACTER_UPDATE_INVENTORY,  // SEND
    CHARACTER_UPDATE_WALLET,     // SEND
    CHARACTER_UPDATE_ACTION,     // SEND - RECEIVE

    // Location related messages
    LOCATION_UPDATE_ACTIONS,  // SEND
    LOCATION_UPDATE_POSITION, // SEND - RECEIVE
};

} // namespace System::Message

#endif // MESSAGETYPE_H
