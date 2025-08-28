#ifndef LOCATIONACTIONLOOT_H
#define LOCATIONACTIONLOOT_H

#include <string>

namespace Model {

class LocationActionLoot {
public:
    LocationActionLoot();

    std::string id() const;
    void setId( const std::string& id );

    double baseAmount() const;
    void setBaseAmount( double baseAmount );

    double modifierAmount() const;
    void setModifierAmount( double modifierAmount );

    double baseChance() const;
    void setBaseChance( double baseChance );

    double modifierChance() const;
    void setModifierChance( double modifierChance );

    double realAmountByLevel( int skillLevel ) const;
    double realChanceByLevel( int skillLevel ) const;

private:
    std::string _id;
    double _baseAmount;
    double _modifierAmount;
    double _baseChance;
    double _modifierChance;
};

} // namespace Model

#endif // LOCATIONACTIONLOOT_H
