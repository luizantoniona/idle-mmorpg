#include "CharacterCoordinates.h"

namespace Domain {

CharacterCoordinates::CharacterCoordinates() :
    _locationId( "" ),
    _spawnLocationId( "" ),
    _structureId( "" ),
    _spawnStructureId( "" ) {}

Json::Value CharacterCoordinates::toJson() {
    Json::Value root;
    root[ "location" ] = locationId();
    root[ "structure" ] = structureId();
    return root;
}

std::string CharacterCoordinates::locationId() const {
    return _locationId;
}

void CharacterCoordinates::setLocationId( const std::string& locationId ) {
    _locationId = locationId;
}

std::string CharacterCoordinates::spawnLocationId() const {
    return _spawnLocationId;
}

void CharacterCoordinates::setSpawnLocationId( const std::string& locationId ) {
    _spawnLocationId = locationId;
}

std::string CharacterCoordinates::structureId() const {
    return _structureId;
}

void CharacterCoordinates::setStructureId( const std::string& structureId ) {
    _structureId = structureId;
}

std::string CharacterCoordinates::spawnStructureId() const {
    return _spawnStructureId;
}

void CharacterCoordinates::setSpawnStructureId( const std::string& structureId ) {
    _spawnStructureId = structureId;
}

} // namespace Domain
