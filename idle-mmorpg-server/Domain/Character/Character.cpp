#include "Character.h"

namespace Domain {

Character::Character() :
    _idCharacter( 0 ),
    _idUser( 0 ),
    _name( "" ),
    // --- Persistent Data
    _equipment(),
    _inventory(),
    _progression(),
    _skills(),
    _spells(),
    _stage(),
    _vitals(),
    _wallet(),
    // --- Runtime Data

Json::Value Character::toJson() {
    Json::Value root;
    root[ "idUser" ] = idUser();
    root[ "idCharacter" ] = idCharacter();
    root[ "name" ] = name();
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

std::string Character::name() const {
    return _name;
}

void Character::setName( const std::string& name ) {
    _name = name;
}

CharacterEquipment& Character::equipment() {
    return _equipment;
}

void Character::setEquipment( const CharacterEquipment& equipment ) {
    _equipment = equipment;
}

CharacterInventory& Character::inventory() {
    return _inventory;
}

void Character::setInventory( const CharacterInventory& inventory ) {
    _inventory = inventory;
}

CharacterProgression& Character::progression() {
    return _progression;
}

void Character::setProgression( const CharacterProgression& progression ) {
    _progression = progression;
}

CharacterSkills& Character::skills() {
    return _skills;
}

void Character::setSkills( const CharacterSkills& skills ) {
    _skills = skills;
}

CharacterSpells& Character::spells() {
    return _spells;
}

void Character::setSpells( const CharacterSpells& spells ) {
    _spells = spells;
}

CharacterStage& Character::stage() {
    return _stage;
}

void Character::setStage( const CharacterStage& stage ) {
    _stage = stage;
}

CharacterVitals& Character::vitals() {
    return _vitals;
}

void Character::setVitals( const CharacterVitals& vitals ) {
    _vitals = vitals;
}

CharacterWallet& Character::wallet() {
    return _wallet;
}

void Character::setWallet( const CharacterWallet& wallet ) {
    _wallet = wallet;
}

} // namespace Domain
