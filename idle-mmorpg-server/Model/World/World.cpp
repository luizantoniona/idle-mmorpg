#include "World.h"

namespace Model {

World::World() :
    _regions() {
}

std::vector<std::unique_ptr<Region> >& World::regions() {
    return _regions;
}

void World::setRegions( std::vector<std::unique_ptr<Region> > regions ) {
    _regions = std::move( regions );
}

void World::addRegion( std::unique_ptr<Region> region ) {
    _regions.push_back( std::move( region ) );
}

} // namespace Model
