#ifndef MESSAGERECEIVERTYPE_H
#define MESSAGERECEIVERTYPE_H

namespace Core::Message {

enum class MessageReceiverType {
    UNKNOWN,

    CHARACTER_UPDATE_ACTION,
    CHARACTER_UPDATE_LOCATION,
};

} // namespace Core::Message

#endif // MESSAGERECEIVERTYPE_H
