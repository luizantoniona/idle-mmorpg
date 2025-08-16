#ifndef CHARACTEREQUIPMENT_H
#define CHARACTEREQUIPMENT_H

#include <json/json.h>

#include "CharacterEquipmentItem.h"

namespace Model {

class CharacterEquipment {
public:
    CharacterEquipment();

    Json::Value toJson();

    CharacterEquipmentItem& helmet();
    void setHelmet( const CharacterEquipmentItem& helmet );

    CharacterEquipmentItem& armor();
    void setArmor( const CharacterEquipmentItem& armor );

    CharacterEquipmentItem& leg();
    void setLeg( const CharacterEquipmentItem& leg );

    CharacterEquipmentItem& boot();
    void setBoot( const CharacterEquipmentItem& boot );

    CharacterEquipmentItem& glove();
    void setGlove( const CharacterEquipmentItem& glove );

    CharacterEquipmentItem& leftHand();
    void setLeftHand( const CharacterEquipmentItem& leftHand );

    CharacterEquipmentItem& rightHand();
    void setRightHand( const CharacterEquipmentItem& rightHand );

    CharacterEquipmentItem& amulet();
    void setAmulet( const CharacterEquipmentItem& amulet );

    CharacterEquipmentItem& ring();
    void setRing( const CharacterEquipmentItem& ring );

    CharacterEquipmentItem& pickaxe();
    void setPickaxe( const CharacterEquipmentItem& pickaxe );

    CharacterEquipmentItem& woodaxe();
    void setWoodaxe( const CharacterEquipmentItem& woodaxe );

    CharacterEquipmentItem& fishrod();
    void setFishrod( const CharacterEquipmentItem& fishrod );

    CharacterEquipmentItem& shovel();
    void setShovel( const CharacterEquipmentItem& shovel );

    CharacterEquipmentItem& sickle();
    void setSickle( const CharacterEquipmentItem& sickle );

private:
    CharacterEquipmentItem _helmet;
    CharacterEquipmentItem _armor;
    CharacterEquipmentItem _leg;
    CharacterEquipmentItem _boot;
    CharacterEquipmentItem _glove;

    CharacterEquipmentItem _leftHand;
    CharacterEquipmentItem _rightHand;

    CharacterEquipmentItem _amulet;
    CharacterEquipmentItem _ring;

    CharacterEquipmentItem _pickaxe;
    CharacterEquipmentItem _woodaxe;
    CharacterEquipmentItem _fishrod;
    CharacterEquipmentItem _shovel;
    CharacterEquipmentItem _sickle;
};

} // namespace Model

#endif // CHARACTEREQUIPMENT_H
