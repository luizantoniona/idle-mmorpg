#include "ActionFactory.h"

#include <iostream>

#include <Domain/Action/ActionHelper.h>
#include <Engine/Manager/Server/ServerConfigurationManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

namespace Manager {

std::unordered_map<Domain::ActionType, std::unique_ptr<Domain::Action>> ActionFactory::createActions( const std::string& actionsPath ) {
    std::cout << "ActionFactory::createActions" << std::endl;

    std::unordered_map<Domain::ActionType, std::unique_ptr<Domain::Action>> actions;

    Json::Value actionsJson = Helper::JsonHelper::loadJsonFile( actionsPath + "actions.json" );

    for ( const auto& actionEntry : actionsJson[ "actions" ] ) {
        std::string actionFilePath = actionsPath + actionEntry.asString() + ".json";

        auto action = createAction( actionFilePath );
        if ( action ) {
            actions[ action->type() ] = std::move( action );

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
    Domain::ActionType type = Domain::ActionHelper::stringToType( actionId );

    if ( type == Domain::ActionType::UNKNOWN ) {
        std::cerr << "Unmapped action: " << actionId << std::endl;
        return nullptr;
    }

    auto action = std::make_unique<Domain::Action>();
    action->setType( type );
    action->setDescription( actionJson[ "description" ].asString() );

    // --- Requirement ---
    if ( actionJson.isMember( "requirement" ) ) {
        Domain::ActionRequirement requirement;

        requirement.setStage( actionJson[ "requirement" ][ "stage" ].asInt() );
        requirement.setLevel( actionJson[ "requirement" ][ "level" ].asInt() );

        action->setRequirement( requirement );
    }

    // --- Options ---
    if ( actionJson.isMember( "options" ) ) {
        for ( const auto& optionJson : actionJson[ "options" ] ) {
            Domain::ActionOption option;

            option.setStage( optionJson[ "stage" ].asInt() );
            option.setDuration( optionJson[ "duration" ].asInt() * Commons::Singleton<Manager::ServerConfigurationManager>::instance().tickRate() );
            option.setItemId( optionJson[ "item" ].asString() );

            action->addOption( option );
        }
    }

    return action;
}

} // namespace Manager
