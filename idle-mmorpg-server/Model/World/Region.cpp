#include "Region.h"

namespace Model {

Region::Region() :
    _id( "" ),
    _name( "" ),
    _description( "" ),
    _locations() {
}

std::string Region::id() const {
    return _id;
}

void Region::setId( const std::string& id ) {
    _id = id;
}

std::string Region::name() const {
    return _name;
}

void Region::setName( const std::string& name ) {
    _name = name;
}

std::string Region::description() const {
    return _description;
}

void Region::setDescription( const std::string& description ) {
    _description = description;
}

std::vector<std::unique_ptr<Location>>& Region::locations() {
    return _locations;
}

void Region::setLocations( std::vector<std::unique_ptr<Location>> locations ) {
    _locations = std::move( locations );
}

void Region::addLocation( std::unique_ptr<Location> location ) {
    _locations.push_back( std::move( location ) );
}

Location* Region::locationById( const std::string& locationId ) {
    for ( const auto& locationPtr : _locations ) {
        if ( locationPtr->id() == locationId ) {
            return locationPtr.get();
        }
    }

    return nullptr;
}

bool Region::hasLocationWithCoordinates( int x, int y, int z ) const {
    for ( const auto& location : _locations ) {
        if ( location->x() == x && location->y() == y && location->z() == z ) {
            return true;
        }
    }

    return false;
}

Location* Region::locationByCoordinates( int x, int y, int z ) {
    for ( const auto& location : _locations ) {
        if ( location->x() == x && location->y() == y && location->z() == z ) {
            return location.get();
        }
    }

    return nullptr;
}

} // namespace Model
