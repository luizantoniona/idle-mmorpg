#include "CharacterEquipment.h"

namespace Model {

CharacterEquipment::CharacterEquipment() :
    _helmet(),
    _armor(),
    _leg(),
    _boot(),
    _glove(),
    _leftHand(),
    _rightHand(),
    _amulet(),
    _ring(),
    _pickaxe(),
    _woodaxe(),
    _fishrod(),
    _shovel(),
    _sickle() {
}

Json::Value CharacterEquipment::toJson() {
    Json::Value root;
    root[ "helmet" ] = helmet().toJson();
    root[ "armor" ] = armor().toJson();
    root[ "leg" ] = leg().toJson();
    root[ "boot" ] = boot().toJson();
    root[ "glove" ] = glove().toJson();
    root[ "leftHand" ] = leftHand().toJson();
    root[ "righHand" ] = rightHand().toJson();
    root[ "amulet" ] = amulet().toJson();
    root[ "ring" ] = ring().toJson();
    root[ "pickaxe" ] = pickaxe().toJson();
    root[ "woodaxe" ] = woodaxe().toJson();
    root[ "fishrod" ] = fishrod().toJson();
    root[ "shovel" ] = shovel().toJson();
    root[ "sickle" ] = sickle().toJson();
    return root;
}

CharacterEquipmentItem CharacterEquipment::helmet() const {
    return _helmet;
}

void CharacterEquipment::setHelmet( const CharacterEquipmentItem& helmet ) {
    _helmet = helmet;
}

CharacterEquipmentItem CharacterEquipment::armor() const {
    return _armor;
}

void CharacterEquipment::setArmor( const CharacterEquipmentItem& armor ) {
    _armor = armor;
}

CharacterEquipmentItem CharacterEquipment::leg() const {
    return _leg;
}

void CharacterEquipment::setLeg( const CharacterEquipmentItem& leg ) {
    _leg = leg;
}

CharacterEquipmentItem CharacterEquipment::boot() const {
    return _boot;
}

void CharacterEquipment::setBoot( const CharacterEquipmentItem& boot ) {
    _boot = boot;
}

CharacterEquipmentItem CharacterEquipment::glove() const {
    return _glove;
}

void CharacterEquipment::setGlove( const CharacterEquipmentItem& glove ) {
    _glove = glove;
}

CharacterEquipmentItem CharacterEquipment::leftHand() const {
    return _leftHand;
}

void CharacterEquipment::setLeftHand( const CharacterEquipmentItem& leftHand ) {
    _leftHand = leftHand;
}

CharacterEquipmentItem CharacterEquipment::rightHand() const {
    return _rightHand;
}

void CharacterEquipment::setRightHand( const CharacterEquipmentItem& rightHand ) {
    _rightHand = rightHand;
}

CharacterEquipmentItem CharacterEquipment::amulet() const {
    return _amulet;
}

void CharacterEquipment::setAmulet( const CharacterEquipmentItem& amulet ) {
    _amulet = amulet;
}

CharacterEquipmentItem CharacterEquipment::ring() const {
    return _ring;
}

void CharacterEquipment::setRing( const CharacterEquipmentItem& ring ) {
    _ring = ring;
}

CharacterEquipmentItem CharacterEquipment::pickaxe() const {
    return _pickaxe;
}

void CharacterEquipment::setPickaxe( const CharacterEquipmentItem& pickaxe ) {
    _pickaxe = pickaxe;
}

CharacterEquipmentItem CharacterEquipment::woodaxe() const {
    return _woodaxe;
}

void CharacterEquipment::setWoodaxe( const CharacterEquipmentItem& woodaxe ) {
    _woodaxe = woodaxe;
}

CharacterEquipmentItem CharacterEquipment::fishrod() const {
    return _fishrod;
}

void CharacterEquipment::setFishrod( const CharacterEquipmentItem& fishrod ) {
    _fishrod = fishrod;
}

CharacterEquipmentItem CharacterEquipment::shovel() const {
    return _shovel;
}

void CharacterEquipment::setShovel( const CharacterEquipmentItem& shovel ) {
    _shovel = shovel;
}

CharacterEquipmentItem CharacterEquipment::sickle() const {
    return _sickle;
}

void CharacterEquipment::setSickle( const CharacterEquipmentItem& sickle ) {
    _sickle = sickle;
}

} // namespace Model
