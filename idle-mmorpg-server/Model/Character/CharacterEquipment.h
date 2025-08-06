#ifndef CHARACTEREQUIPMENT_H
#define CHARACTEREQUIPMENT_H

#include <json/json.h>

#include "CharacterEquipmentItem.h"

namespace Model {

class CharacterEquipment {
public:
    CharacterEquipment();

    Json::Value toJson();

    CharacterEquipmentItem head() const;
    void setHead( const CharacterEquipmentItem& head );

    CharacterEquipmentItem chest() const;
    void setChest( const CharacterEquipmentItem& chest );

    CharacterEquipmentItem legs() const;
    void setLegs( const CharacterEquipmentItem& legs );

    CharacterEquipmentItem boots() const;
    void setBoots( const CharacterEquipmentItem& boots );

    CharacterEquipmentItem gloves() const;
    void setGloves( const CharacterEquipmentItem& gloves );

    CharacterEquipmentItem leftHand() const;
    void setLeftHand( const CharacterEquipmentItem& leftHand );

    CharacterEquipmentItem rightHand() const;
    void setRightHand( const CharacterEquipmentItem& rightHand );

    CharacterEquipmentItem amulet() const;
    void setAmulet( const CharacterEquipmentItem& amulet );

    CharacterEquipmentItem ring() const;
    void setRing( const CharacterEquipmentItem& ring );

private:
    CharacterEquipmentItem _head;
    CharacterEquipmentItem _chest;
    CharacterEquipmentItem _legs;
    CharacterEquipmentItem _boots;
    CharacterEquipmentItem _gloves;

    CharacterEquipmentItem _leftHand;
    CharacterEquipmentItem _rightHand;

    CharacterEquipmentItem _amulet;
    CharacterEquipmentItem _ring;
};

} // namespace Model

#endif // CHARACTEREQUIPMENT_H
