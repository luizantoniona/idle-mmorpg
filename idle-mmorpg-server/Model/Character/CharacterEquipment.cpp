#include "CharacterEquipment.h"

namespace {
constexpr const char* JSON_HEAD = "head";
constexpr const char* JSON_CHEST = "chest";
constexpr const char* JSON_LEGS = "legs";
constexpr const char* JSON_BOOTS = "boots";
constexpr const char* JSON_GLOVES = "gloves";
constexpr const char* JSON_LEFT_HAND = "leftHand";
constexpr const char* JSON_RIGHT_HAND = "righHand";
constexpr const char* JSON_AMULET = "amulet";
constexpr const char* JSON_RING = "ring";
} // namespace

namespace Model {

CharacterEquipment::CharacterEquipment() :
    _head(),
    _chest(),
    _legs(),
    _boots(),
    _gloves(),
    _leftHand(),
    _rightHand(),
    _amulet(),
    _ring() {
}

Json::Value CharacterEquipment::toJson() {
    Json::Value root;
    root[ JSON_HEAD ] = head().toJson();
    root[ JSON_CHEST ] = chest().toJson();
    root[ JSON_LEGS ] = legs().toJson();
    root[ JSON_BOOTS ] = boots().toJson();
    root[ JSON_GLOVES ] = gloves().toJson();
    root[ JSON_LEFT_HAND ] = leftHand().toJson();
    root[ JSON_RIGHT_HAND ] = rightHand().toJson();
    root[ JSON_AMULET ] = amulet().toJson();
    root[ JSON_RING ] = ring().toJson();
    return root;
}

CharacterEquipmentItem CharacterEquipment::head() const {
    return _head;
}

void CharacterEquipment::setHead( const CharacterEquipmentItem& head ) {
    _head = head;
}

CharacterEquipmentItem CharacterEquipment::chest() const {
    return _chest;
}

void CharacterEquipment::setChest( const CharacterEquipmentItem& chest ) {
    _chest = chest;
}

CharacterEquipmentItem CharacterEquipment::legs() const {
    return _legs;
}

void CharacterEquipment::setLegs( const CharacterEquipmentItem& legs ) {
    _legs = legs;
}

CharacterEquipmentItem CharacterEquipment::boots() const {
    return _boots;
}

void CharacterEquipment::setBoots( const CharacterEquipmentItem& boots ) {
    _boots = boots;
}

CharacterEquipmentItem CharacterEquipment::gloves() const {
    return _gloves;
}

void CharacterEquipment::setGloves( const CharacterEquipmentItem& gloves ) {
    _gloves = gloves;
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

} // namespace Model
