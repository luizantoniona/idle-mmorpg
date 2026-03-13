#include "StageFactory.h"

#include <iostream>

#include <Engine/Manager/Creature/CreatureManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

namespace Manager {

std::unique_ptr<Domain::Stage> StageFactory::createStage( const std::string& stageFile ) {
    std::cout << "StageFactory::createStage Creating Stage: " << stageFile << std::endl;

    Json::Value stageJson = Helper::JsonHelper::loadJsonFile( stageFile );

    auto stage = std::make_unique<Domain::Stage>();
    stage->setLevel( stageJson[ "level" ].asInt() );

    // --- Creatures ---
    for ( const Json::Value& creatureJson : stageJson[ "creatures" ] ) {
        Domain::StageCreature creature;
        creature.setId( creatureJson[ "id" ].asString() );
        creature.setAmount( creatureJson[ "amount" ].asInt() );
        creature.setCreature( Commons::Singleton<Manager::CreatureManager>::instance().creatureById( creature.id() ) );
        stage->addCreature( creature );
    }

    // --- Objectives ---
    for ( const Json::Value& objectiveJson : stageJson[ "objectives" ] ) {
        Domain::StageObjective objective;
        objective.setType( objectiveJson[ "type" ].asString() );
        objective.setTarget( objectiveJson[ "target" ].asString() );
        objective.setAmount( objectiveJson[ "amount" ].asInt() );
        stage->addObjective( objective );
    }

    // --- Rewards ---
    for ( const Json::Value& rewardJson : stageJson[ "rewards" ] ) {
        Domain::StageReward reward;
        reward.setType( rewardJson[ "type" ].asString() );
        reward.setId( rewardJson[ "id" ].asString() );
        reward.setAmount( rewardJson[ "amount" ].asInt() );
        stage->addReward( reward );
    }

    return stage;
}

} // namespace Manager
