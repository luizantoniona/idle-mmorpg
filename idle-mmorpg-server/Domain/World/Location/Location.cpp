#include "Location.h"

namespace Domain {

Location::Location() :
    _id( "" ),
    _name( "" ),
    _description( "" ),
    _tileSizeX( 0 ),
    _tileSizeY( 0 ),
    _denizens( {} ),
    _actions( {} ),
    _creatures( {} ),
    _structures( {} ),
    _connections( {} ) {}

Json::Value Location::toJson() const {
    Json::Value root;
    root[ "id" ] = id();
    root[ "name" ] = name();
    root[ "description" ] = description();
    root[ "sizeX" ] = tileSizeX();
    root[ "sizeY" ] = tileSizeY();

    for ( auto& structure : structures() ) {
        root[ "structures" ].append( structure.toJson() );
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

int Location::tileSizeX() const {
    return _tileSizeX;
}

void Location::setTileSizeX( int tileSizeX ) {
    _tileSizeX = tileSizeX;
}

int Location::tileSizeY() const {
    return _tileSizeY;
}

void Location::setTileSizeY( int tileSizeY ) {
    _tileSizeY = tileSizeY;
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

bool Location::hasStructure( const std::string& structureId ) {
    for ( const auto& structure : _structures ) {
        if ( structure.id() == structureId ) {
            return true;
        }
    }

    return false;
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

} // namespace Domain
