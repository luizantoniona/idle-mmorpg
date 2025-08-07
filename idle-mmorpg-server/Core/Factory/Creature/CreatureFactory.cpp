#include "CreatureFactory.h"

#include <iostream>

#include <Commons/JsonHelper.h>

namespace Core::Factory {

std::unordered_map<std::string, std::unique_ptr<Model::Creature> > CreatureFactory::createCreatures( const std::string& creaturesPath ) {
    std::cout << "CreatureFactory::createCreatures" << std::endl;

    std::unordered_map<std::string, std::unique_ptr<Model::Creature> > creatures;

    // TODO: implement

    std::cout << "CreatureFactory::createCreatures Number of creatures loaded: " << creatures.size() << std::endl;

    return creatures;
}

std::unique_ptr<Model::Creature> CreatureFactory::createCreature( const std::string& creaturePath ) {
    std::cout << "CreatureFactory::createCreature: " << creaturePath << std::endl;

    Json::Value creatureJson = Commons::JsonHelper::loadJsonFile( creaturePath );

    auto creature = std::make_unique<Model::Creature>();

    // TODO: implement

    return creature;
}

} // namespace Core::Factory
