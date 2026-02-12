#include "Action.h"

namespace Domain {

Action::Action() {}

std::string Action::id() const {
    return _id;
}

void Action::setId( const std::string& id ) {
    _id = id;
}

ActionType Action::type() const {
    return _type;
}

void Action::setType( ActionType type ) {
    _type = type;
}

} // namespace Domain
