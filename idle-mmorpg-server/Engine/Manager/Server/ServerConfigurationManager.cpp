#include "ServerConfigurationManager.h"

#include <iostream>

#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

#include "Engine/Manager/Server/ServerImageManager.h"

namespace Manager {

ServerConfigurationManager::ServerConfigurationManager() :
    _vitalsRate{ 10, 10, 10 },
    _tickRate( 20 ),
    _threadPool( 4 ),
    _baseExperience( 0.00 ),
    _growthRate( 0.00 ) {
}

void ServerConfigurationManager::initialize( const std::string& configurationPath ) {
    std::cout << "ServerConfigurationManager::initialize" << std::endl;

    Json::Value configurationJson = Helper::JsonHelper::loadJsonFile( configurationPath + "configuration.json" );

    // --- Vitals Rate ---
    _vitalsRate.health = configurationJson[ "rates" ][ "levelUp" ][ "health" ].asInt();
    _vitalsRate.mana = configurationJson[ "rates" ][ "levelUp" ][ "mana" ].asInt();
    _vitalsRate.stamina = configurationJson[ "rates" ][ "levelUp" ][ "stamina" ].asInt();

    // --- Server Images ---
    std::string logoFile = configurationJson[ "server" ][ "logo" ].asString();
    Commons::Singleton<Manager::ServerImageManager>::instance().loadImage( "logo.png", configurationPath + logoFile );

    // TODO: Create separated structs for general configurations
    _tickRate = configurationJson[ "server" ].get( "tickRate", 20 ).asInt();
    _baseExperience = configurationJson[ "rates" ][ "progression" ][ "baseExperience" ].asDouble();
    _growthRate = configurationJson[ "rates" ][ "progression" ][ "growthRate" ].asDouble();

    std::cout << "ServerConfigurationManager::initialize"
              << " [TICK_RATE] " << _tickRate
              << " [BASE_EXPERIENCE] " << _baseExperience
              << " [GROWTH_RATE] " << _growthRate
              << std::endl;
}

const VitalRate& ServerConfigurationManager::vitalsRate() const {
    return _vitalsRate;
}

// TODO: Create separated structs for general configurations
int ServerConfigurationManager::tickRate() const {
    return _tickRate;
}

int ServerConfigurationManager::threadPool() const {
    return _threadPool;
}

double ServerConfigurationManager::baseExperience() const {
    return _baseExperience;
}

double ServerConfigurationManager::growthRate() const {
    return _growthRate;
}

} // namespace Manager
