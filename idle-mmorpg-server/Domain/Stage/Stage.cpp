#include "Stage.h"

namespace Domain {

Stage::Stage() :
    _id( "" ),
    _level( 0 ),
    _creatures( {} ),
    _objectives( {} ) {
}

Stage::~Stage() = default;

Json::Value Stage::toJson() {
    Json::Value values;
    values[ "id" ] = id();
    values[ "level" ] = level();

    for ( auto& objective : objectives() ) {
        values[ "objectives" ].append( objective.toJson() );
    }

    Json::Value stage;
    stage[ "stage" ] = values;
    return stage;
}

std::string Stage::id() const {
    return _id;
}

void Stage::setId( const std::string& id ) {
    _id = id;
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

} // namespace Domain
