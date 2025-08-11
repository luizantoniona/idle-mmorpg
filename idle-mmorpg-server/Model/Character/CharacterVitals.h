#ifndef CHARACTERVITALS_H
#define CHARACTERVITALS_H

#include <json/json.h>

namespace Model {

class CharacterVitals {
public:
    CharacterVitals();

    Json::Value toJson();

    double health() const;
    void setHealth( double health );

    double maxHealth() const;
    void setMaxHealth( double maxHealth );

    double baseHealthRegen() const;
    void setBaseHealthRegen( double baseHealthRegen );

    double modifierHealthRegen() const;
    void setModifierHealthRegen( double modifierHealthRegen );

    double mana() const;
    void setMana( double mana );

    double maxMana() const;
    void setMaxMana( double maxMana );

    double baseManaRegen() const;
    void setBaseManaRegen( double baseManaRegen );

    double modifierManaRegen() const;
    void setModifierManaRegen( double modifierManaRegen );

    double stamina() const;
    void setStamina( double stamina );

    double maxStamina() const;
    void setMaxStamina( double maxStamina );

    double baseStaminaRegen() const;
    void setBaseStaminaRegen( double baseStaminaRegen );

    double modifierStaminaRegen() const;
    void setModifierStaminaRegen( double modifierStaminaRegen );

    double healthRegen() const;
    double manaRegen() const;
    double staminaRegen() const;

private:
    double _health;
    double _maxHealth;
    double _baseHealthRegen;
    double _modifierHealthRegen;

    double _mana;
    double _maxMana;
    double _baseManaRegen;
    double _modifierManaRegen;

    double _stamina;
    double _maxStamina;
    double _baseStaminaRegen;
    double _modifierStaminaRegen;
};

} // namespace Model

#endif // CHARACTERVITALS_H
