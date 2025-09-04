#include "Character.h"

namespace Model {

Character::Character() :
    _idCharacter( 0 ),
    _idUser( 0 ),
    _name( "" ),
    _action(),
    _attributes(),
    _combatAction(),
    _coordinates(),
    _equipment(),
    _inventory(),
    _progression(),
    _skills(),
    _vitals(),
    _wallet() {
}

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

CharacterCombatAction& Character::combatAction() {
    return _combatAction;
}

void Character::setCombatAction( const CharacterCombatAction& combatAction ) {
    _combatAction = combatAction;
}

CharacterCoordinates& Character::coordinates() {
    return _coordinates;
}

void Character::setCoordinates( const CharacterCoordinates& coordinates ) {
    _coordinates = coordinates;
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

CharacterQuests& Character::quests() {
    return _quests;
}

void Character::setQuests( const CharacterQuests& quests ) {
    _quests = quests;
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

} // namespace Model
