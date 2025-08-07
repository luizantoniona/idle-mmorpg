#include "Creature.h"

namespace Model {

Creature::Creature() :
    _id( "" ),
    _type( "" ),
    _name( "" ),
    _description( "" ),
    _experience( 0 ),
    _health( 0.0 ),
    _mana( 0.0 ),
    _defense( 0.0 ),
    _evasion( 0.0 ),
    _maxAttack( 0.0 ),
    _minAttack( 0.0 ),
    _loot( {} ) {}

std::string Creature::id() const {
    return _id;
}

void Creature::setId( const std::string& id ) {
    _id = id;
}

std::string Creature::type() const {
    return _type;
}

void Creature::setType( const std::string& type ) {
    _type = type;
}

std::string Creature::name() const {
    return _name;
}

void Creature::setName( const std::string& name ) {
    _name = name;
}

std::string Creature::description() const {
    return _description;
}

void Creature::setDescription( const std::string& description ) {
    _description = description;
}

int Creature::experience() const {
    return _experience;
}

void Creature::setExperience( int experience ) {
    _experience = experience;
}

double Creature::health() const {
    return _health;
}

void Creature::setHealth( double health ) {
    _health = health;
}

double Creature::mana() const {
    return _mana;
}

void Creature::setMana( double mana ) {
    _mana = mana;
}

double Creature::defense() const {
    return _defense;
}

void Creature::setDefense( double defense ) {
    _defense = defense;
}

double Creature::evasion() const {
    return _evasion;
}

void Creature::setEvasion( double evasion ) {
    _evasion = evasion;
}

double Creature::maxAttack() const {
    return _maxAttack;
}

void Creature::setMaxAttack( double maxAttack ) {
    _maxAttack = maxAttack;
}

double Creature::minAttack() const {
    return _minAttack;
}

void Creature::setMinAttack( double minAttack ) {
    _minAttack = minAttack;
}

std::vector<CreatureLoot> Creature::loot() const {
    return _loot;
}

void Creature::setLoot( const std::vector<CreatureLoot>& loot ) {
    _loot = loot;
}

void Creature::addLoot( const CreatureLoot& loot ) {
    _loot.push_back( loot );
}

} // namespace Model
