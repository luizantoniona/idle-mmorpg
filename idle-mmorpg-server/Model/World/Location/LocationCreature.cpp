#include "LocationCreature.h"

namespace Model {

LocationCreature::LocationCreature() :
    _id( "" ),
    _structure( "" ),
    _min( 0 ),
    _max( 0 ),
    _creature( nullptr ) {}

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

int LocationCreature::min() const {
    return _min;
}

void LocationCreature::setMin( int min ) {
    _min = min;
}

int LocationCreature::max() const {
    return _max;
}

void LocationCreature::setMax( int max ) {
    _max = max;
}

Creature* LocationCreature::creature() const {
    return _creature;
}

void LocationCreature::setCreature( Creature* creature ) {
    _creature = creature;
}

} // namespace Model
