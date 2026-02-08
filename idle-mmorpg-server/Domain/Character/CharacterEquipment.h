#ifndef CHARACTEREQUIPMENT_H
#define CHARACTEREQUIPMENT_H

#include <json/json.h>

#include "CharacterEquipmentItem.h"

namespace Domain {

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

    CharacterEquipmentItem& weapon();
    void setWeapon( const CharacterEquipmentItem& weapon );

    CharacterEquipmentItem& offhand();
    void setOffhand( const CharacterEquipmentItem& offhand );

    CharacterEquipmentItem& amulet();
    void setAmulet( const CharacterEquipmentItem& amulet );

    CharacterEquipmentItem& ring();
    void setRing( const CharacterEquipmentItem& ring );

    CharacterEquipmentItem& pickaxe();
    void setPickaxe( const CharacterEquipmentItem& pickaxe );

    CharacterEquipmentItem& woodaxe();
    void setWoodaxe( const CharacterEquipmentItem& woodaxe );

    CharacterEquipmentItem& fishingrod();
    void setFishingrod( const CharacterEquipmentItem& fishingrod );

    CharacterEquipmentItem& sickle();
    void setSickle( const CharacterEquipmentItem& sickle );

private:
    CharacterEquipmentItem _helmet;
    CharacterEquipmentItem _armor;
    CharacterEquipmentItem _leg;
    CharacterEquipmentItem _boot;

    CharacterEquipmentItem _weapon;
    CharacterEquipmentItem _offhand;

    CharacterEquipmentItem _amulet;
    CharacterEquipmentItem _ring;

    CharacterEquipmentItem _pickaxe;
    CharacterEquipmentItem _woodaxe;
    CharacterEquipmentItem _fishingrod;
    CharacterEquipmentItem _sickle;
};

} // namespace Domain

#endif // CHARACTEREQUIPMENT_H
