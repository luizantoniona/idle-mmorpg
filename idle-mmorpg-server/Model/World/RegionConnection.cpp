#include "RegionConnection.h"

namespace Model {

RegionConnection::RegionConnection() :
    _origin( "" ),
    _destination( "" ) {}

std::string RegionConnection::origin() const {
    return _origin;
}

void RegionConnection::setOrigin( const std::string& origin ) {
    _origin = origin;
}

std::string RegionConnection::destination() const {
    return _destination;
}

void RegionConnection::setDestination( const std::string& destination ) {
    _destination = destination;
}

} // namespace Model
