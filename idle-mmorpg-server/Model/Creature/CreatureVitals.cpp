#include "CreatureVitals.h"

namespace Model {

CreatureVitals::CreatureVitals() {
}

Json::Value CreatureVitals::toJson() {
    Json::Value root;
    root[ "health" ] = health();
    root[ "maxHealth" ] = maxHealth();
    root[ "mana" ] = mana();
    root[ "maxMana" ] = maxMana();
    root[ "stamina" ] = stamina();
    root[ "maxStamina" ] = maxStamina();

    return root;
}

double CreatureVitals::health() const {
    return _health;
}

void CreatureVitals::setHealth( double health ) {
    _health = health;
}

double CreatureVitals::maxHealth() const {
    return _maxHealth;
}

void CreatureVitals::setMaxHealth( double maxHealth ) {
    _maxHealth = maxHealth;
}

double CreatureVitals::mana() const {
    return _mana;
}

void CreatureVitals::setMana( double mana ) {
    _mana = mana;
}

double CreatureVitals::maxMana() const {
    return _maxMana;
}

void CreatureVitals::setMaxMana( double maxMana ) {
    _maxMana = maxMana;
}

double CreatureVitals::stamina() const {
    return _stamina;
}

void CreatureVitals::setStamina( double stamina ) {
    _stamina = stamina;
}

double CreatureVitals::maxStamina() const {
    return _maxStamina;
}

void CreatureVitals::setMaxStamina( double maxStamina ) {
    _maxStamina = maxStamina;
}

} // namespace Model
