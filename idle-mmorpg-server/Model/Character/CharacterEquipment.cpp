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
constexpr const char* JSON_PICKAXE = "pickaxe";
constexpr const char* JSON_WOODAXE = "woodaxe";
constexpr const char* JSON_ROD = "rod";
constexpr const char* JSON_SHOVEL = "shovel";
constexpr const char* JSON_SICKLE = "sickle";
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
    _ring(),
    _pickaxe(),
    _woodaxe(),
    _rod(),
    _shovel(),
    _sickle() {}

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
    root[ JSON_PICKAXE ] = pickaxe().toJson();
    root[ JSON_WOODAXE ] = woodaxe().toJson();
    root[ JSON_ROD ] = rod().toJson();
    root[ JSON_SHOVEL ] = shovel().toJson();
    root[ JSON_SICKLE ] = sickle().toJson();
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

CharacterEquipmentItem CharacterEquipment::rod() const {
    return _rod;
}

void CharacterEquipment::setRod( const CharacterEquipmentItem& rod ) {
    _rod = rod;
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
