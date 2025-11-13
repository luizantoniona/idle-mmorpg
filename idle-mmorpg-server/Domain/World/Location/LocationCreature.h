#ifndef LOCATIONCREATURE_H
#define LOCATIONCREATURE_H

#include <string>

#include <Domain/Creature/Creature.h>

namespace Domain {

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

    const Creature* creature() const;
    void setCreature( const Creature* creature );

private:
    std::string _id;
    std::string _structure;
    int _spawnMin;
    int _spawnMax;
    const Creature* _creature;
};

} // namespace Domain

#endif // LOCATIONCREATURE_H
