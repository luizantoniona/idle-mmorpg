#ifndef CREATUREVITALS_H
#define CREATUREVITALS_H

#include <json/json.h>

namespace Model {

class CreatureVitals {
public:
    CreatureVitals();

    Json::Value toJson();

    double health() const;
    void setHealth( double health );

    double maxHealth() const;
    void setMaxHealth( double maxHealth );

    double mana() const;
    void setMana( double mana );

    double maxMana() const;
    void setMaxMana( double maxMana );

    double stamina() const;
    void setStamina( double stamina );

    double maxStamina() const;
    void setMaxStamina( double maxStamina );

private:
    double _health;
    double _maxHealth;

    double _mana;
    double _maxMana;

    double _stamina;
    double _maxStamina;
};

} // namespace Model

#endif // CREATUREVITALS_H
