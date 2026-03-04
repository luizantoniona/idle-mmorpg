#include "WorldFactory.h"

#include <iostream>

#include <Shared/Helper/JsonHelper.h>

#include "StageFactory.h"

namespace Manager {

std::unique_ptr<Domain::World> WorldFactory::createWorld( const std::string& mapPath ) {
    std::cout << "WorldFactory::createWorld" << std::endl;

    std::unique_ptr<Domain::World> world = std::make_unique<Domain::World>();

    Json::Value worldJson = Helper::JsonHelper::loadJsonFile( mapPath + "world.json" );

    if ( !worldJson.isMember( "stages" ) || !worldJson[ "stages" ].isArray() ) {
        std::cerr << "WorldFactory::createWorld missing or invalid 'stages' array in world.json" << std::endl;
        return nullptr;
    }

    for ( const Json::Value& stageJson : worldJson[ "stages" ] ) {
        std::string stageFile = mapPath + stageJson.asString() + ".json";

        auto stage = StageFactory::createStage( stageFile );

        if ( !stage ) {
            std::cerr << "WorldFactory::createWorld failed to load stage: " << stageFile << std::endl;
            continue;
        }

        world->addStage( std::move( stage ) );
    }

    std::cout << "WorldFactory::createWorld Number of stages loaded: " << world->stages().size() << std::endl;

    return world;
}

} // namespace Manager
