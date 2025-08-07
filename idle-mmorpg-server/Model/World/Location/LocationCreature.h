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

    int min() const;
    void setMin( int min );

    int max() const;
    void setMax( int max );

    Creature* creature() const;
    void setCreature( Creature* creature );

private:
    std::string _id;
    std::string _structure;
    int _min;
    int _max;
    Creature* _creature;
};

} // namespace Model

#endif // LOCATIONCREATURE_H
