#include "ActionFactory.h"

#include <iostream>

#include <Domain/Action/ActionHelper.h>
#include <Engine/Manager/Server/ServerConfigurationManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

namespace Manager {

std::unordered_map<std::string, std::unique_ptr<Domain::Action> > ActionFactory::createActions( const std::string& actionsPath ) {
    std::cout << "ActionFactory::createActions" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Domain::Action> > actions;

    Json::Value actionsJson = Helper::JsonHelper::loadJsonFile( actionsPath + "actions.json" );

    for ( const auto& actionEntry : actionsJson[ "actions" ] ) {
        std::string actionFilePath = actionsPath + actionEntry.asString() + ".json";

        auto action = createAction( actionFilePath );
        if ( action ) {
            actions[ action->id() ] = std::move( action );

        } else {
            std::cerr << "Failed to load action: " << actionFilePath << std::endl;
        }
    }

    std::cout << "ActionFactory::createActions Number of actions loaded: " << actions.size() << std::endl;

    return actions;
}

std::unique_ptr<Domain::Action> ActionFactory::createAction( const std::string& actionPath ) {
    std::cout << "ActionFactory::createAction: " << actionPath << std::endl;

    Json::Value actionJson = Helper::JsonHelper::loadJsonFile( actionPath );

    const std::string actionId = actionJson[ "id" ].asString();

    if ( Domain::ActionHelper::stringToType( actionId ) == Domain::ActionType::UNKNOWN ) {
        std::cerr << "Unmaped action: " << actionId << std::endl;
        return nullptr;
    }

    auto action = std::make_unique<Domain::Action>();

    action->setId( actionId );
    action->setType( Domain::ActionHelper::stringToType( actionId ) );

    return action;
}

} // namespace Manager
