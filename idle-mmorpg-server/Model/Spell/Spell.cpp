#include "Spell.h"

namespace Model {

Spell::Spell() :
    _id( "" ),
    _name( "" ),
    _description( "" ),
    _icon( "" ),
    _type( "" ),
    _manaCost( 0 ),
    _cooldown( 0 ),
    _effect() {
}

std::string Spell::id() const {
    return _id;
}

void Spell::setId( const std::string& id ) {
    _id = id;
}

std::string Spell::name() const {
    return _name;
}

void Spell::setName( const std::string& name ) {
    _name = name;
}

std::string Spell::description() const {
    return _description;
}

void Spell::setDescription( const std::string& description ) {
    _description = description;
}

std::string Spell::icon() const {
    return _icon;
}

void Spell::setIcon( const std::string& icon ) {
    _icon = icon;
}

std::string Spell::type() const {
    return _type;
}

void Spell::setType( const std::string& type ) {
    _type = type;
}

int Spell::manaCost() const {
    return _manaCost;
}

void Spell::setManaCost( int manaCost ) {
    _manaCost = manaCost;
}

int Spell::cooldown() const {
    return _cooldown;
}

void Spell::setCooldown( int cooldown ) {
    _cooldown = cooldown;
}

SpellEffect& Spell::effect() {
    return _effect;
}

void Spell::setEffect( const SpellEffect& effect ) {
    _effect = effect;
}

} // namespace Model
