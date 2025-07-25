#include "World.h"

namespace Model {

World::World() :
    _regions(),
    _connections() {}

std::vector<std::unique_ptr<Region> >& World::regions() {
    return _regions;
}

void World::setRegions( std::vector<std::unique_ptr<Region> > regions ) {
    _regions = std::move( regions );
}

void World::addRegion( std::unique_ptr<Region> region ) {
    _regions.push_back( std::move( region ) );
}

std::vector<std::unique_ptr<RegionConnection> >& World::connections() {
    return _connections;
}

void World::setConnections( std::vector<std::unique_ptr<RegionConnection> > connections ) {
    _connections = std::move( connections );
}

void World::addConnection( std::unique_ptr<RegionConnection> connection ) {
    _connections.push_back( std::move( connection ) );
}

} // namespace Model
