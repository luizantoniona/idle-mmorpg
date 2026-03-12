#ifndef ITEMEFFECT_H
#define ITEMEFFECT_H

#include <json/json.h>

namespace Domain {

class ItemEffect {
public:
    ItemEffect();

    Json::Value toJson() const;

    double health() const;
    void setHealth( double health );

    double mana() const;
    void setMana( double mana );

    double stamina() const;
    void setStamina( double stamina );

    int duration() const;
    void setDuration( int duration );

private:
    double _health;
    double _mana;
    double _stamina;
    int _duration;
};

} // namespace Domain

#endif // ITEMEFFECT_H
