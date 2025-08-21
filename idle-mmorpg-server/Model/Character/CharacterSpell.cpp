#include "CharacterSpell.h"

namespace Model {

CharacterSpell::CharacterSpell() :
    _id( "" ),
    _count( 0 ),
    _spell( nullptr ) {}

Json::Value CharacterSpell::toJson() const {
    Json::Value root;
    root[ "id" ] = id();
    root[ "count" ] = count();
    if ( spell() ) {
        root[ "name" ] = spell()->name();
        root[ "description" ] = spell()->description();
        root[ "icon" ] = spell()->icon();
        root[ "type" ] = spell()->type();
        root[ "manaCost" ] = spell()->manaCost();
        root[ "cooldown" ] = spell()->cooldown();
    }
    return root;
}

std::string CharacterSpell::id() const {
    return _id;
}

void CharacterSpell::setId( const std::string& id ) {
    _id = id;
}

int CharacterSpell::count() const {
    return _count;
}

void CharacterSpell::setCount( int count ) {
    _count = count;
}

Spell* CharacterSpell::spell() const {
    return _spell;
}

void CharacterSpell::setSpell( Spell* spell ) {
    _spell = spell;
}

bool CharacterSpell::isReady() {
    return _count >= _spell->cooldown();
}

} // namespace Model
