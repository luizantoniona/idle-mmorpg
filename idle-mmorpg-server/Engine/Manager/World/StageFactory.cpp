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
    stage->setId( stageJson[ "id" ].asString() );
    stage->setLevel( stageJson[ "level" ].asInt() );

    // --- Creatures ---
    for ( const Json::Value& creatureJson : stageJson[ "creatures" ] ) {
        Domain::StageCreature creature;
        creature.setId( creatureJson[ "id" ].asString() );
        creature.setCreature( Commons::Singleton<Manager::CreatureManager>::instance().creatureById( creature.id() ) );

        stage->addCreature( creature );
    }

    // --- Objectives ---
    for ( const Json::Value& objectiveJson : stageJson[ "objectives" ] ) {
        Domain::StageObjective objective;
        objective.setId( objectiveJson[ "id" ].asString() );
        objective.setTarget( objectiveJson[ "target" ].asString() );
        objective.setAmount( objectiveJson[ "amount" ].asInt() );

        for ( const Json::Value& rewardJson : objectiveJson[ "rewards" ] ) {
            Domain::StageObjectiveReward reward;
            reward.setType( rewardJson[ "type" ].asString() );
            reward.setId( rewardJson[ "id" ].asString() );
            reward.setAmount( rewardJson[ "amount" ].asInt() );

            objective.addReward( reward );
        }

        stage->addObjective( objective );
    }

    return stage;
}

} // namespace Manager
