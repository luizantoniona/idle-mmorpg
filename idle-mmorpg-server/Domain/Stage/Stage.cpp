#include "Stage.h"

namespace Domain {

Stage::Stage() :
    _id( "" ),
    _name( "" ),
    _creatures( {} ),
    _objectives( {} ) {
}

Stage::~Stage() = default;

std::string Stage::id() const {
    return _id;
}

void Stage::setId( const std::string& id ) {
    _id = id;
}

std::string Stage::name() const {
    return _name;
}

void Stage::setName( const std::string& name ) {
    _name = name;
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
