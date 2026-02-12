#ifndef ACTIONTYPE_H
#define ACTIONTYPE_H

namespace Domain {

enum class ActionType {
    IDLE,

    TRAIN,
    COMBAT,

    UNKNOWN,
};

} // namespace Domain

#endif // ACTIONTYPE_H
