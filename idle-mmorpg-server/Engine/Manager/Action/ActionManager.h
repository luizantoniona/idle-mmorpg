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

    Domain::Action* actionById( const std::string& actionId );

private:
    std::unordered_map<std::string, std::unique_ptr<Domain::Action> > _actions;
};

} //namespace Manager

#endif // ACTIONMANAGER_H
