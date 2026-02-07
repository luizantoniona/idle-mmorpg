#include "World.h"

namespace Domain {

World::World() :
    _stages() {
}

std::vector<std::unique_ptr<Stage>>& World::stages() {
    return _stages;
}

const std::vector<std::unique_ptr<Stage>>& World::stages() const {
    return _stages;
}

void World::setStages( std::vector<std::unique_ptr<Stage>> stages ) {
    _stages = std::move( stages );
}

void World::addStage( std::unique_ptr<Stage> stage ) {
    _stages.push_back( std::move( stage ) );
}

Stage* World::stageById( const std::string& stageId ) {
    for ( const auto& stage : _stages ) {
        if ( stage->id() == stageId ) {
            return stage.get();
        }
    }
    return nullptr;
}

bool World::hasStageById( const std::string& stageId ) const {
    for ( const auto& stage : _stages ) {
        if ( stage->id() == stageId ) {
            return true;
        }
    }
    return false;
}

} // namespace Domain
