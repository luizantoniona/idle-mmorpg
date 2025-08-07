#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>

#include "CreatureLoot.h"

namespace Model {

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

    int experience() const;
    void setExperience( int experience );

    double health() const;
    void setHealth( double health );

    double mana() const;
    void setMana( double mana );

    double defense() const;
    void setDefense( double defense );

    double evasion() const;
    void setEvasion( double evasion );

    double maxAttack() const;
    void setMaxAttack( double maxAttack );

    double minAttack() const;
    void setMinAttack( double minAttack );

    std::vector<CreatureLoot> loot() const;
    void setLoot( const std::vector<CreatureLoot>& loot );
    void addLoot( const CreatureLoot& loot );

private:
    std::string _id;
    std::string _type;
    std::string _name;
    std::string _description;
    int _experience;
    double _health;
    double _mana;
    double _defense;
    double _evasion;
    double _maxAttack;
    double _minAttack;
    std::vector<CreatureLoot> _loot;
};

} // namespace Model

#endif // CREATURE_H
