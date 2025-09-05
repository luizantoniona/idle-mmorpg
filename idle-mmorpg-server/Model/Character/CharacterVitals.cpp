#include "CharacterVitals.h"

#include <Commons/Singleton.h>
#include <Core/Manager/ServerConfigurationManager.h>

namespace Model {

CharacterVitals::CharacterVitals() :
    _health( 0.0 ),
    _maxHealth( 0.0 ),
    _mana( 0.0 ),
    _maxMana( 0.0 ),
    _stamina( 0.0 ),
    _maxStamina( 0.0 ),
    _regenDuration( Commons::Singleton<Core::Manager::ServerConfigurationManager>::instance().tickRate() ),
    _regenCounter( 0 ) {}

Json::Value CharacterVitals::toJson() {
    Json::Value root;
    root[ "health" ] = health();
    root[ "maxHealth" ] = maxHealth();
    root[ "mana" ] = mana();
    root[ "maxMana" ] = maxMana();
    root[ "stamina" ] = stamina();
    root[ "maxStamina" ] = maxStamina();
    return root;
}

double CharacterVitals::health() const {
    return _health;
}

void CharacterVitals::setHealth( double health ) {
    _health = health;
}

double CharacterVitals::maxHealth() const {
    return _maxHealth;
}

void CharacterVitals::setMaxHealth( double maxHealth ) {
    _maxHealth = maxHealth;
}

double CharacterVitals::mana() const {
    return _mana;
}

void CharacterVitals::setMana( double mana ) {
    _mana = mana;
}

double CharacterVitals::maxMana() const {
    return _maxMana;
}

void CharacterVitals::setMaxMana( double maxMana ) {
    _maxMana = maxMana;
}

double CharacterVitals::stamina() const {
    return _stamina;
}

void CharacterVitals::setStamina( double stamina ) {
    _stamina = stamina;
}

double CharacterVitals::maxStamina() const {
    return _maxStamina;
}

void CharacterVitals::setMaxStamina( double maxStamina ) {
    _maxStamina = maxStamina;
}

int CharacterVitals::regenDuration() const {
    return _regenDuration;
}

void CharacterVitals::setRegenDuration( int regenDuration ) {
    _regenDuration = regenDuration;
}

int CharacterVitals::regenCounter() const {
    return _regenCounter;
}

void CharacterVitals::setRegenCounter( int regenCounter ) {
    _regenCounter = regenCounter;
}

} // namespace Model
