#include "CharacterCoordinates.h"

namespace Model {

CharacterCoordinates::CharacterCoordinates() :
    _x( 0 ),
    _y( 0 ),
    _z( 0 ),
    _xSpawn( 0 ),
    _ySpawn( 0 ),
    _zSpawn( 0 ) {}

Json::Value CharacterCoordinates::toJson() {
    Json::Value root;

    root[ "x" ] = x();
    root[ "y" ] = y();
    root[ "z" ] = z();

    root[ "xSpawn" ] = xSpawn();
    root[ "ySpawn" ] = ySpawn();
    root[ "zSpawn" ] = zSpawn();

    return root;
}

int CharacterCoordinates::x() const {
    return _x;
}

void CharacterCoordinates::setX( int x ) {
    _x = x;
}

int CharacterCoordinates::y() const {
    return _y;
}

void CharacterCoordinates::setY( int y ) {
    _y = y;
}

int CharacterCoordinates::z() const {
    return _z;
}

void CharacterCoordinates::setZ( int z ) {
    _z = z;
}

int CharacterCoordinates::xSpawn() const {
    return _xSpawn;
}

void CharacterCoordinates::setXSpawn( int xSpawn ) {
    _xSpawn = xSpawn;
}

int CharacterCoordinates::ySpawn() const {
    return _ySpawn;
}

void CharacterCoordinates::setYSpawn( int ySpawn ) {
    _ySpawn = ySpawn;
}

int CharacterCoordinates::zSpawn() const {
    return _zSpawn;
}

void CharacterCoordinates::setZSpawn( int zSpawn ) {
    _zSpawn = zSpawn;
}

} // namespace Model
