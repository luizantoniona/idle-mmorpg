#ifndef ACTIONMANAGER_H
#define ACTIONMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Action/Action.h>

namespace Manager {

class ActionManager {
public:
    ActionManager();

    void initialize( const std::string& actionsPath );

    const std::unordered_map<Domain::ActionType, std::unique_ptr<Domain::Action>>& actions() const;

    Domain::Action* actionById( Domain::ActionType actionType );

private:
    std::unordered_map<Domain::ActionType, std::unique_ptr<Domain::Action>> _actions;
};

} // namespace Manager

#endif // ACTIONMANAGER_H
