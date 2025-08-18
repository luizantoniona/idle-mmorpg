#include "CharacterVitals.h"

namespace Model {

CharacterVitals::CharacterVitals() :
    _health( 0.0 ),
    _maxHealth( 0.0 ),
    _modifierMaxHealth( 0.0 ),
    _baseHealthRegen( 0.0 ),
    _modifierHealthRegen( 0.0 ),
    _mana( 0.0 ),
    _maxMana( 0.0 ),
    _modifierMaxMana( 0.0 ),
    _baseManaRegen( 0.0 ),
    _modifierManaRegen( 0.0 ),
    _stamina( 0.0 ),
    _maxStamina( 0.0 ),
    _modifierMaxStamina( 0.0 ),
    _baseStaminaRegen( 0.0 ),
    _modifierStaminaRegen( 0.0 ),
    _regenDuration( 20 ),
    _regenCounter( 0 ) {
}

Json::Value CharacterVitals::toJson() {
    Json::Value root;
    root[ "health" ] = health();
    root[ "maxHealth" ] = fullHealth();
    root[ "regenHealth" ] = baseHealthRegen() + modifierHealthRegen();

    root[ "mana" ] = mana();
    root[ "maxMana" ] = fullMana();
    root[ "regenMana" ] = baseManaRegen() + modifierManaRegen();

    root[ "stamina" ] = stamina();
    root[ "maxStamina" ] = fullStamina();
    root[ "regenStamina" ] = baseStaminaRegen() + modifierStaminaRegen();

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

double CharacterVitals::modifierMaxHealth() const {
    return _modifierMaxHealth;
}

void CharacterVitals::setModifierMaxHealth( double modifierMaxHealth ) {
    _modifierMaxHealth = modifierMaxHealth;
}

double CharacterVitals::baseHealthRegen() const {
    return _baseHealthRegen;
}

void CharacterVitals::setBaseHealthRegen( double baseHealthRegen ) {
    _baseHealthRegen = baseHealthRegen;
}

double CharacterVitals::modifierHealthRegen() const {
    return _modifierHealthRegen;
}

void CharacterVitals::setModifierHealthRegen( double modifierHealthRegen ) {
    _modifierHealthRegen = modifierHealthRegen;
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

double CharacterVitals::modifierMaxMana() const {
    return _modifierMaxMana;
}

void CharacterVitals::setModifierMaxMana( double modifierMaxMana ) {
    _modifierMaxMana = modifierMaxMana;
}

double CharacterVitals::baseManaRegen() const {
    return _baseManaRegen;
}

void CharacterVitals::setBaseManaRegen( double baseManaRegen ) {
    _baseManaRegen = baseManaRegen;
}

double CharacterVitals::modifierManaRegen() const {
    return _modifierManaRegen;
}

void CharacterVitals::setModifierManaRegen( double modifierManaRegen ) {
    _modifierManaRegen = modifierManaRegen;
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

double CharacterVitals::modifierMaxStamina() const {
    return _modifierMaxStamina;
}

void CharacterVitals::setModifierMaxStamina( double modifierMaxStamina ) {
    _modifierMaxStamina = modifierMaxStamina;
}

double CharacterVitals::baseStaminaRegen() const {
    return _baseStaminaRegen;
}

void CharacterVitals::setBaseStaminaRegen( double baseStaminaRegen ) {
    _baseStaminaRegen = baseStaminaRegen;
}

double CharacterVitals::modifierStaminaRegen() const {
    return _modifierStaminaRegen;
}

void CharacterVitals::setModifierStaminaRegen( double modifierStaminaRegen ) {
    _modifierStaminaRegen = modifierStaminaRegen;
}

double CharacterVitals::fullHealth() const {
    return _maxHealth + _modifierMaxHealth;
}

double CharacterVitals::fullMana() const {
    return _maxMana + _modifierMaxMana;
}

double CharacterVitals::fullStamina() const {
    return _maxStamina + _modifierMaxStamina;
}

double CharacterVitals::healthRegen() const {
    return _baseHealthRegen + _modifierHealthRegen;
}

double CharacterVitals::manaRegen() const {
    return _baseManaRegen + _modifierManaRegen;
}

double CharacterVitals::staminaRegen() const {
    return _baseStaminaRegen + _modifierStaminaRegen;
}

void CharacterVitals::resetModifiers() {
    _modifierMaxHealth = 0;
    // _modifierHealthRegen = 0;
    _modifierMaxMana = 0;
    // _modifierManaRegen = 0;
    _modifierMaxStamina = 0;
    // _modifierStaminaRegen = 0;
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
