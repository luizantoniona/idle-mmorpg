#ifndef ITEMCOMBAT_H
#define ITEMCOMBAT_H

#include <json/json.h>

namespace Domain {

class ItemCombat {
public:
    ItemCombat();

    Json::Value toJson() const;

    double attack() const;
    void setAttack( double attack );

    double defense() const;
    void setDefense( double defense );

private:
    double _attack;
    double _defense;
};

} // namespace Domain

#endif // ITEMCOMBAT_H
