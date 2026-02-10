#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Action/Action.h>

namespace Manager {

class ActionFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Domain::Action> > createActions( const std::string& actionsPath );

private:
    static std::unique_ptr<Domain::Action> createAction( const std::string& actionPath );
};

} // namespace Manager

#endif // ACTIONFACTORY_H
