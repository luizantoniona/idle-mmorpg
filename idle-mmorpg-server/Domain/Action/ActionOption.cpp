#include "ActionOption.h"

namespace Domain {

ActionOption::ActionOption() :
    _stage( 0 ) {
}

int ActionOption::stage() const {
    return _stage;
}

void ActionOption::setStage( int stage ) {
    _stage = stage;
}

const std::string& ActionOption::itemId() const {
    return _itemId;
}

void ActionOption::setItemId( const std::string& id ) {
    _itemId = id;
}

} // namespace Domain
