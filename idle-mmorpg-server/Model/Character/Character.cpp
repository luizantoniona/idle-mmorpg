#include "Character.h"

namespace Model {

Character::Character() :
    _idCharacter( 0 ),
    _idUser( 0 ),
    _dsName( "" ),
    _action(),
    _attributes(),
    _coordinates(),
    _inventory(),
    _skills(),
    _wallet() {
}

Json::Value Character::toJson() {
    Json::Value root;

    root[ "idUser" ] = idUser();
    root[ "idCharacter" ] = idCharacter();
    root[ "dsName" ] = dsName();

    return root;
}

int Character::idCharacter() const {
    return _idCharacter;
}

void Character::setIdCharacter( int idCharacter ) {
    _idCharacter = idCharacter;
}

int Character::idUser() const {
    return _idUser;
}

void Character::setIdUser( int idUser ) {
    _idUser = idUser;
}

std::string Character::dsName() const {
    return _dsName;
}

void Character::setDsName( const std::string& dsName ) {
    _dsName = dsName;
}

CharacterAction& Character::action() {
    return _action;
}

void Character::setAction( const CharacterAction& action ) {
    _action = action;
}

CharacterAttributes& Character::attributes() {
    return _attributes;
}

void Character::setAttributes( const CharacterAttributes& attributes ) {
    _attributes = attributes;
}

CharacterCoordinates& Character::coordinates() {
    return _coordinates;
}

void Character::setCoordinates( const CharacterCoordinates& coordinates ) {
    _coordinates = coordinates;
}

CharacterInventory& Character::inventory() {
    return _inventory;
}

void Character::setInventory( const CharacterInventory& inventory ) {
    _inventory = inventory;
}

CharacterSkills& Character::skills() {
    return _skills;
}

void Character::setSkills( const CharacterSkills& skills ) {
    _skills = skills;
}

CharacterWallet& Character::wallet() {
    return _wallet;
}

void Character::setWallet( const CharacterWallet& wallet ) {
    _wallet = wallet;
}

} // namespace Model
