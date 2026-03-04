#include "CharacterVitals.h"

namespace Domain {

CharacterVitals::CharacterVitals() :
    _health( 0.0 ),
    _maxHealth( 0.0 ),
    _mana( 0.0 ),
    _maxMana( 0.0 ),
    _stamina( 0.0 ),
    _maxStamina( 0.0 ),
    _regenDuration( 0 ),
    _regenCounter( 0 ) {}

Json::Value CharacterVitals::toJson() {
    Json::Value values;
    values[ "health" ] = health();
    values[ "maxHealth" ] = maxHealth();
    values[ "mana" ] = mana();
    values[ "maxMana" ] = maxMana();
    values[ "stamina" ] = stamina();
    values[ "maxStamina" ] = maxStamina();

    Json::Value vitals;
    vitals[ "vitals" ] = values;
    return vitals;
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

void CharacterVitals::modifyHealth( double delta ) {
    _health += delta;

    if ( _health > _maxHealth ) {
        _health = _maxHealth;
    }

    if ( _health < 0.0 ) {
        _health = 0.0;
    }
}

void CharacterVitals::modifyMana( double delta ) {
    _mana += delta;

    if ( _mana > _maxMana ) {
        _mana = _maxMana;
    }

    if ( _mana < 0.0 ) {
        _mana = 0.0;
    }
}

void CharacterVitals::modifyStamina( double delta ) {
    _stamina += delta;

    if ( _stamina > _maxStamina ) {
        _stamina = _maxStamina;
    }

    if ( _stamina < 0.0 ) {
        _stamina = 0.0;
    }
}

void CharacterVitals::modifyMaxHealth( double delta ) {
    _maxHealth += delta;
}

void CharacterVitals::modifyMaxMana( double delta ) {
    _maxMana += delta;
}

void CharacterVitals::modifyMaxStamina( double delta ) {
    _maxStamina += delta;
}

} // namespace Domain
