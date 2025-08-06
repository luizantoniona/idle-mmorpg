#include "Location.h"

namespace {
constexpr const char* JSON_ID = "id";
constexpr const char* JSON_NAME = "name";
constexpr const char* JSON_DESCRIPTION = "description";
constexpr const char* JSON_X = "x";
constexpr const char* JSON_Y = "y";
constexpr const char* JSON_Z = "z";
constexpr const char* JSON_STRUCTURES = "structures";
} // namespace

namespace Model {

Location::Location() :
    _id( "" ),
    _name( "" ),
    _description( "" ),
    _x( 0 ),
    _y( 0 ),
    _z( 0 ),
    _actions( {} ),
    _structures( {} ) {}

Json::Value Location::toJson() {
    Json::Value root;
    root[ JSON_ID ] = id();
    root[ JSON_NAME ] = name();
    root[ JSON_DESCRIPTION ] = description();
    root[ JSON_X ] = x();
    root[ JSON_Y ] = y();
    root[ JSON_Z ] = z();

    for ( auto& structure : structures() ) {
        root[JSON_STRUCTURES].append( structure.toJson() );
    }

    return root;
}

std::string Location::id() const {
    return _id;
}

void Location::setId( const std::string& id ) {
    _id = id;
}

std::string Location::name() const {
    return _name;
}

void Location::setName( const std::string& name ) {
    _name = name;
}

std::string Location::description() const {
    return _description;
}

void Location::setDescription( const std::string& description ) {
    _description = description;
}

int Location::x() const {
    return _x;
}

void Location::setX( int x ) {
    _x = x;
}

int Location::y() const {
    return _y;
}

void Location::setY( int y ) {
    _y = y;
}

int Location::z() const {
    return _z;
}

void Location::setZ( int z ) {
    _z = z;
}

const std::vector<LocationAction>& Location::actions() const {
    return _actions;
}

void Location::setActions( const std::vector<LocationAction>& actions ) {
    _actions = actions;
}

void Location::addAction( const LocationAction& action ) {
    _actions.push_back( action );
}

const std::vector<LocationStructure>& Location::structures() const {
    return _structures;
}

void Location::setStructures( const std::vector<LocationStructure>& structures ) {
    _structures = structures;
}

void Location::addStructure( const LocationStructure& structure ) {
    _structures.push_back( structure );
}

} // namespace Model
