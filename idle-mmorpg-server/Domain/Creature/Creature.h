#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>

#include "CreatureAction.h"
#include "CreatureLoot.h"
#include "CreatureVitals.h"

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

    CreatureAction& action();
    void setAction( const CreatureAction& action );

    CreatureVitals& vitals();
    void setVitals( const CreatureVitals& vitals );

    std::vector<CreatureLoot> loot() const;
    void setLoot( const std::vector<CreatureLoot>& loot );
    void addLoot( const CreatureLoot& loot );

private:
    std::string _id;
    std::string _type;
    std::string _name;
    std::string _description;
    std::string _icon;

    CreatureAction _action;
    CreatureVitals _vitals;

    std::vector<CreatureLoot> _loot;
};

} // namespace Domain

#endif // CREATURE_H
