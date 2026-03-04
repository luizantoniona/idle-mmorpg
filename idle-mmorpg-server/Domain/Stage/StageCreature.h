#ifndef STAGECREATURE_H
#define STAGECREATURE_H

#include <Domain/Creature/Creature.h>

namespace Domain {

class StageCreature {
public:
    StageCreature();
    ~StageCreature();

    std::string id() const;
    void setId( const std::string& id );

    int amount() const;
    void setAmount( int amount );

    const Creature* creature() const;
    void setCreature( const Creature* creature );

private:
    std::string _id;
    int _amount;
    const Creature* _creature;
};

} // namespace Domain

#endif // STAGECREATURE_H
