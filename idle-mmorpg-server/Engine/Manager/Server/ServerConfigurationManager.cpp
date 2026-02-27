#include "ServerConfigurationManager.h"

#include <iostream>

#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

#include "Engine/Manager/Server/ServerImageManager.h"

namespace Manager {

ServerConfigurationManager::ServerConfigurationManager() :
    _tickRate( 0 ),
    _threadPool( 4 ),
    _baseExperience( 0.00 ),
    _growthRate( 0.00 ) {
}

void ServerConfigurationManager::initialize( const std::string& configurationPath ) {
    std::cout << "ServerConfigurationManager::initialize" << std::endl;

    Json::Value configurationJson = Helper::JsonHelper::loadJsonFile( configurationPath + "configuration.json" );

    _tickRate = configurationJson[ "tickRate" ].asInt();
    _baseExperience = configurationJson[ "experience" ][ "baseExperience" ].asDouble();
    _growthRate = configurationJson[ "experience" ][ "growthRate" ].asDouble();

    std::string logoFile = configurationJson[ "logo" ].asString();
    Commons::Singleton<Manager::ServerImageManager>::instance().loadImage( "logo.png", configurationPath + logoFile );

    std::cout << "ServerConfigurationManager::initialize"
              << " [TICK_RATE] " << _tickRate
              << " [BASE_EXPERIENCE] " << _baseExperience
              << " [GROWTH_RATE] " << _growthRate << std::endl;
}

int ServerConfigurationManager::tickRate() const {
    return _tickRate;
}

void ServerConfigurationManager::setTickRate( int tickRate ) {
    _tickRate = tickRate;
}

int ServerConfigurationManager::threadPool() const {
    return _threadPool;
}

void ServerConfigurationManager::setThreadPool( int threadPool ) {
    _threadPool = threadPool;
}

} // namespace Manager
