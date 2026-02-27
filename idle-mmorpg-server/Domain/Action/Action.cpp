#include "Action.h"

namespace Domain {

Action::Action() :
    _type( ActionType::UNKNOWN ) {
}

ActionType Action::type() const {
    return _type;
}

void Action::setType( ActionType type ) {
    _type = type;
}

std::string Action::description() const {
    return _description;
}

void Action::setDescription( const std::string& description ) {
    _description = description;
}

const std::vector<ActionOption>& Action::options() const {
    return _options;
}

void Action::addOption( const ActionOption& option ) {
    _options.push_back( option );
}

} // namespace Domain
