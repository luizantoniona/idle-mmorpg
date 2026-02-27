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

Stage* World::stageByLevel( int stageLevel ) {
    for ( const auto& stage : _stages ) {
        if ( stage->level() == stageLevel ) {
            return stage.get();
        }
    }
    return nullptr;
}

bool World::hasStageByLevel( int stageLevel ) const {
    for ( const auto& stage : _stages ) {
        if ( stage->level() == stageLevel ) {
            return true;
        }
    }
    return false;
}

} // namespace Domain
