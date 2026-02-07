#include "Creature.h"

namespace Domain {

Creature::Creature() :
    _id( "" ),
    _type( "" ),
    _name( "" ),
    _description( "" ),
    _icon( "" ),
    _action(),
    _vitals() {
}

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

std::string Creature::icon() const {
    return _icon;
}

void Creature::setIcon( const std::string& icon ) {
    _icon = icon;
}

CreatureAction& Creature::action() {
    return _action;
}

void Creature::setAction( const CreatureAction& action ) {
    _action = action;
}

CreatureVitals& Creature::vitals() {
    return _vitals;
}

void Creature::setVitals( const CreatureVitals& vitals ) {
    _vitals = vitals;
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

} // namespace Domain
