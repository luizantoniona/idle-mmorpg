#include "LocationConnection.h"

namespace {
constexpr const char* JSON_DESTINATION = "destination";
constexpr const char* JSON_DIRECTION = "direction";
} // namespace

namespace Model {

LocationConnection::LocationConnection() :
    _destination( "" ),
    _direction( "" ) {}

Json::Value LocationConnection::toJson() {
    Json::Value root;
    root[ JSON_DESTINATION ] = destination();
    root[ JSON_DIRECTION ] = direction();
    return root;
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
