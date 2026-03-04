#include "ActionManager.h"

#include "ActionFactory.h"

namespace Manager {

ActionManager::ActionManager() :
    _actions() {}

void ActionManager::initialize( const std::string& actionsPath ) {
    _actions = ActionFactory::createActions( actionsPath );
}

const std::unordered_map<Domain::ActionType, std::unique_ptr<Domain::Action>>& ActionManager::actions() const {
    return _actions;
}

Domain::Action* ActionManager::actionById( Domain::ActionType actionType ) {
    auto it = _actions.find( actionType );
    if ( it != _actions.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Manager
