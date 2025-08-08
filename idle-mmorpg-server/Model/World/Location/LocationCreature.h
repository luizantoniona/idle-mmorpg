#ifndef LOCATIONCREATURE_H
#define LOCATIONCREATURE_H

#include <string>

#include <Model/Creature/Creature.h>

namespace Model {

class LocationCreature {
public:
    LocationCreature();

    std::string id() const;
    void setId( const std::string& id );

    std::string structure() const;
    void setStructure( const std::string& structure );

    int spawnMin() const;
    void setSpawnMin( int min );

    int spawnMax() const;
    void setSpawnMax( int max );

    Creature* creature() const;
    void setCreature( Creature* creature );

private:
    std::string _id;
    std::string _structure;
    int _spawnMin;
    int _spawnMax;
    Creature* _creature;
};

} // namespace Model

#endif // LOCATIONCREATURE_H
