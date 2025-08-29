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

bool Region::hasLocationById( const std::string& locationId ) {
    for ( const auto& locationPtr : _locations ) {
        if ( locationPtr->id() == locationId ) {
            return true;
        }
    }

    return false;
}

} // namespace Model
