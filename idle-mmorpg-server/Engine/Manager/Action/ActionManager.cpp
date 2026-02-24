#include "ActionManager.h"

#include "ActionFactory.h"

namespace Manager {

ActionManager::ActionManager() :
    _actions() {}

void ActionManager::initialize( const std::string& actionsPath ) {
    _actions = ActionFactory::createActions( actionsPath );
}

Domain::Action* ActionManager::actionById( const std::string& actionId ) {
    auto it = _actions.find( actionId );
    if ( it != _actions.end() ) {
        return it->second.get();
    }

    return nullptr;
}

} // namespace Manager
