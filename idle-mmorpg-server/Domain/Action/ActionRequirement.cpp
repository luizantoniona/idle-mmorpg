#include "ActionRequirement.h"

namespace Domain {

ActionRequirement::ActionRequirement() :
    _stage( 0 ),
    _level( 0 ) {
}

int ActionRequirement::stage() const {
    return _stage;
}

void ActionRequirement::setStage( int stage ) {
    _stage = stage;
}

int ActionRequirement::level() const {
    return _level;
}

void ActionRequirement::setLevel( int level ) {
    _level = level;
}

} // namespace Domain
