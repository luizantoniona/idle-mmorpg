#ifndef CHARACTERVITALS_H
#define CHARACTERVITALS_H

#include <json/json.h>

namespace Domain {

class CharacterVitals {
public:
    CharacterVitals();

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

    int regenDuration() const;
    void setRegenDuration( int regenDuration );

    int regenCounter() const;
    void setRegenCounter( int regenCounter );

private:
    double _health;
    double _maxHealth;
    double _mana;
    double _maxMana;
    double _stamina;
    double _maxStamina;
    int _regenDuration;
    int _regenCounter;
};

} // namespace Domain

#endif // CHARACTERVITALS_H
