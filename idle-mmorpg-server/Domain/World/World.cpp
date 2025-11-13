#include "World.h"

namespace Domain {

World::World() :
    _locations() {}

std::vector<std::unique_ptr<Location> >& World::locations() {
    return _locations;
}

void World::setLocations( std::vector<std::unique_ptr<Location> > locations ) {
    _locations = std::move( locations );
}

void World::addLocation( std::unique_ptr<Location> location ) {
    _locations.push_back( std::move( location ) );
}

Location* World::locationById( const std::string& locationId ) {
    for ( const auto& locationPtr : _locations ) {
        if ( locationPtr->id() == locationId ) {
            return locationPtr.get();
        }
    }
    return nullptr;
}

bool World::hasLocationById( const std::string& locationId ) const {
    for ( const auto& locationPtr : _locations ) {
        if ( locationPtr->id() == locationId ) {
            return true;
        }
    }
    return false;
}

} // namespace Domain
