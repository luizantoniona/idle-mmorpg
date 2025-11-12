#ifndef CREATURE_H
#define CREATURE_H

#include <string>
#include <vector>

#include "CreatureCombatAction.h"
#include "CreatureLoot.h"
#include "CreatureVitals.h"

namespace Domain {

class Creature {
public:
    Creature();

    std::string id() const;
    void setId( const std::string& id );

    int combatId() const;
    void setCombatId( int combatId );

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

    CreatureCombatAction& combatAction();
    void setCombatAction( const CreatureCombatAction& combatAction );

    CreatureVitals& vitals();
    void setVitals( const CreatureVitals& vitals );

    double health() const;
    void setHealth( double health );

    double mana() const;
    void setMana( double mana );

    double attack() const;
    void setAttack( double attack );

    double attackSpeed() const;
    void setAttackSpeed( double attackSpeed );

    double accuracy() const;
    void setAccuracy( double accuracy );

    double defense() const;
    void setDefense( double defense );

    double evasion() const;
    void setEvasion( double evasion );

    std::vector<CreatureLoot> loot() const;
    void setLoot( const std::vector<CreatureLoot>& loot );
    void addLoot( const CreatureLoot& loot );

private:
    std::string _id;
    int _combatId;
    std::string _type;
    std::string _name;
    std::string _description;
    std::string _icon;
    int _experience;

    CreatureCombatAction _combatAction;
    CreatureVitals _vitals;

    double _attack;
    double _attackSpeed;
    double _accuracy;
    double _defense;
    double _evasion;

    std::vector<CreatureLoot> _loot;
};

} // namespace Domain

#endif // CREATURE_H
