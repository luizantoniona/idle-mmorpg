#include "Location.h"

namespace Model {

Location::Location() :
    _id( "" ),
    _name( "" ),
    _description( "" ),
    _x( 0 ),
    _y( 0 ),
    _z( 0 ),
    _actions( {} ) {}

Json::Value Location::toJson() {
    Json::Value root;

    root[ "id" ] = id();
    root[ "name" ] = name();
    root[ "description" ] = description();
    root[ "x" ] = x();
    root[ "y" ] = y();
    root[ "z" ] = z();

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

void Location::addAction( const LocationAction action ) {
    _actions.push_back( action );
}

} // namespace Model
