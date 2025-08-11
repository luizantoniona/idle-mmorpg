#include "Creature.h"

namespace Model {

Creature::Creature() :
    _id( "" ),
    _combatId( 0 ),
    _type( "" ),
    _name( "" ),
    _description( "" ),
    _experience( 0 ),
    _vitals(),
    _combatAction(),
    _maxAttack( 0.0 ),
    _minAttack( 0.0 ),
    _accuracy( 0.0 ),
    _speed( 0.0 ),
    _defense( 0.0 ),
    _evasion( 0.0 ),
    _loot( {} ) {
}

std::string Creature::id() const {
    return _id;
}

void Creature::setId( const std::string& id ) {
    _id = id;
}

int Creature::combatId() const {
    return _combatId;
}

void Creature::setCombatId( int combatId ) {
    _combatId = combatId;
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

CreatureCombatAction& Creature::combatAction() {
    return _combatAction;
}

void Creature::setCombatAction( const CreatureCombatAction& combatAction ) {
    _combatAction = combatAction;
}

CreatureVitals& Creature::vitals() {
    return _vitals;
}

void Creature::setVitals( const CreatureVitals& vitals ) {
    _vitals = vitals;
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

double Creature::accuracy() const {
    return _accuracy;
}

void Creature::setAccuracy( double accuracy ) {
    _accuracy = accuracy;
}

double Creature::speed() const {
    return _speed;
}

void Creature::setSpeed( double speed ) {
    _speed = speed;
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
