#include "Stage.h"

namespace Domain {

Stage::Stage() :
    _level( 0 ),
    _creatures( {} ),
    _objectives( {} ) {
}

Stage::~Stage() = default;

Json::Value Stage::toJson() {
    Json::Value values;
    values[ "level" ] = level();

    for ( auto& objective : objectives() ) {
        values[ "objectives" ].append( objective.toJson() );
    }

    Json::Value stage;
    stage[ "stage" ] = values;
    return stage;
}

int Stage::level() const {
    return _level;
}

void Stage::setLevel( int level ) {
    _level = level;
}

std::vector<StageCreature> Stage::creatures() const {
    return _creatures;
}

void Stage::setCreatures( const std::vector<StageCreature>& creatures ) {
    _creatures = creatures;
}

void Stage::addCreature( const StageCreature& creature ) {
    _creatures.push_back( creature );
}

std::vector<StageObjective> Stage::objectives() const {
    return _objectives;
}

void Stage::setObjectives( const std::vector<StageObjective>& objectives ) {
    _objectives = objectives;
}

void Stage::addObjective( const StageObjective& objective ) {
    _objectives.push_back( objective );
}

std::vector<StageReward> Stage::rewards() const {
    return _rewards;
}

void Stage::setRewards( const std::vector<StageReward>& rewards ) {
    _rewards = rewards;
}

void Stage::addReward( const StageReward& reward ) {
    _rewards.push_back( reward );
}

} // namespace Domain
