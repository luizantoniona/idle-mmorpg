#include "Location.h"

namespace {
constexpr const char* JSON_ID = "id";
constexpr const char* JSON_NAME = "name";
constexpr const char* JSON_DESCRIPTION = "description";
constexpr const char* JSON_X = "x";
constexpr const char* JSON_Y = "y";
constexpr const char* JSON_Z = "z";
constexpr const char* JSON_STRUCTURES = "structures";
constexpr const char* JSON_CONNECTIONS = "connections";
} // namespace

namespace Model {

Location::Location() :
    _id( "" ),
    _name( "" ),
    _description( "" ),
    _x( 0 ),
    _y( 0 ),
    _z( 0 ),
    _denizens( {} ),
    _actions( {} ),
    _creatures( {} ),
    _structures( {} ),
    _connections( {} ) {
}

Json::Value Location::toJson() const {
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

std::vector<Denizen> Location::denizens() const {
    return _denizens;
}

void Location::setDenizens( const std::vector<Denizen>& denizens ) {
    _denizens = denizens;
}

void Location::addDenizen( const Denizen& denizen ) {
    _denizens.push_back( denizen );
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

std::vector<LocationCreature> Location::creatures() const {
    return _creatures;
}

void Location::setCreatures( const std::vector<LocationCreature>& creatures ) {
    _creatures = creatures;
}

void Location::addCreature( const LocationCreature& creature ) {
    _creatures.push_back( creature );
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

const std::vector<LocationConnection>& Location::connections() const {
    return _connections;
}

void Location::setConnections( const std::vector<LocationConnection>& connections ) {
    _connections = connections;
}

void Location::addConnection( const LocationConnection& connection ) {
    _connections.push_back( connection );
}

} // namespace Model
