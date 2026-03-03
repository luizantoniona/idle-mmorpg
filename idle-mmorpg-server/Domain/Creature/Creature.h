#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>

#include "CreatureLoot.h"
#include "CreatureVitals.h"

#include "CreatureCombat.h"

namespace Domain {

class Creature {
public:
    Creature();

    std::string id() const;
    void setId( const std::string& id );

    std::string type() const;
    void setType( const std::string& type );

    std::string name() const;
    void setName( const std::string& name );

    std::string description() const;
    void setDescription( const std::string& description );

    std::string icon() const;
    void setIcon( const std::string& icon );

    int experience() const;
    void setExperience( int experience );

    CreatureVitals& vitals();
    void setVitals( const CreatureVitals& vitals );

    std::vector<CreatureLoot> loot() const;
    void setLoot( const std::vector<CreatureLoot>& loot );
    void addLoot( const CreatureLoot& loot );

    // --- Runtime Data
    int combatId() const;
    void setCombatId( int combatId );

    CreatureCombat& combat();
    void setAction( const CreatureCombat& combat );

private:
    std::string _id;
    std::string _type;
    std::string _name;
    std::string _description;
    std::string _icon;
    int _experience;

    CreatureVitals _vitals;
    std::vector<CreatureLoot> _loot;

    // --- Runtime Data
    int _combatId;
    CreatureCombat _combat;
};

} // namespace Domain

#endif // CREATURE_H
