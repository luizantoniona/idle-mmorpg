#include "LocationConnection.h"

namespace Model {

LocationConnection::LocationConnection() :
    _origin( "" ),
    _destination( "" ),
    _direction( "" ) {}

std::string LocationConnection::origin() const {
    return _origin;
}

void LocationConnection::setOrigin( const std::string& origin ) {
    _origin = origin;
}

std::string LocationConnection::destination() const {
    return _destination;
}

void LocationConnection::setDestination( const std::string& destination ) {
    _destination = destination;
}

std::string LocationConnection::direction() const {
    return _direction;
}

void LocationConnection::setDirection( const std::string& direction ) {
    _direction = direction;
}

} // namespace Model
