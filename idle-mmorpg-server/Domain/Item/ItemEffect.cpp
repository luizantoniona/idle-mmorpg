#include "ItemEffect.h"

namespace Domain {

ItemEffect::ItemEffect() :
    _health( 0.0 ),
    _mana( 0.0 ),
    _stamina( 0.0 ),
    _duration( 0 ) {}

Json::Value ItemEffect::toJson() const {
    Json::Value root;
    root[ "health" ] = _health;
    root[ "mana" ] = _mana;
    root[ "stamina" ] = _stamina;
    root[ "duration" ] = _duration;
    return root;
}

double ItemEffect::health() const {
    return _health;
}

void ItemEffect::setHealth( double health ) {
    _health = health;
}

double ItemEffect::mana() const {
    return _mana;
}

void ItemEffect::setMana( double mana ) {
    _mana = mana;
}

double ItemEffect::stamina() const {
    return _stamina;
}

void ItemEffect::setStamina( double stamina ) {
    _stamina = stamina;
}

int ItemEffect::duration() const {
    return _duration;
}

void ItemEffect::setDuration( int duration ) {
    _duration = duration;
}

} // namespace Domain
