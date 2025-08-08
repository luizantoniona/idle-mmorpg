#include "LocationCreature.h"

namespace Model {

LocationCreature::LocationCreature() :
    _id( "" ),
    _structure( "" ),
    _spawnMin( 0 ),
    _spawnMax( 0 ),
    _creature( nullptr ) {
}

std::string LocationCreature::id() const {
    return _id;
}

void LocationCreature::setId( const std::string& id ) {
    _id = id;
}

std::string LocationCreature::structure() const {
    return _structure;
}

void LocationCreature::setStructure( const std::string& structure ) {
    _structure = structure;
}

int LocationCreature::spawnMin() const {
    return _spawnMin;
}

void LocationCreature::setSpawnMin( int spawnMin ) {
    _spawnMin = spawnMin;
}

int LocationCreature::spawnMax() const {
    return _spawnMax;
}

void LocationCreature::setSpawnMax( int spawnMax ) {
    _spawnMax = spawnMax;
}

Creature* LocationCreature::creature() const {
    return _creature;
}

void LocationCreature::setCreature( Creature* creature ) {
    _creature = creature;
}

} // namespace Model
