#ifndef ACTIONTYPE_H
#define ACTIONTYPE_H

namespace Domain {

enum class ActionType {
    IDLE,

    COMBAT,

    TRAIN,

    MINING,

    UNKNOWN,
};

} // namespace Domain

#endif // ACTIONTYPE_H
