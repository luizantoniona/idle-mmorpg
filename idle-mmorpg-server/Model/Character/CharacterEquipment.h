#ifndef CHARACTEREQUIPMENT_H
#define CHARACTEREQUIPMENT_H

#include <json/json.h>

#include "CharacterEquipmentItem.h"

namespace Model {

class CharacterEquipment {
public:
    CharacterEquipment();

    Json::Value toJson();

    CharacterEquipmentItem helmet() const;
    void setHelmet( const CharacterEquipmentItem& helmet );

    CharacterEquipmentItem armor() const;
    void setArmor( const CharacterEquipmentItem& armor );

    CharacterEquipmentItem leg() const;
    void setLeg( const CharacterEquipmentItem& leg );

    CharacterEquipmentItem boot() const;
    void setBoot( const CharacterEquipmentItem& boot );

    CharacterEquipmentItem glove() const;
    void setGlove( const CharacterEquipmentItem& glove );

    CharacterEquipmentItem leftHand() const;
    void setLeftHand( const CharacterEquipmentItem& leftHand );

    CharacterEquipmentItem rightHand() const;
    void setRightHand( const CharacterEquipmentItem& rightHand );

    CharacterEquipmentItem amulet() const;
    void setAmulet( const CharacterEquipmentItem& amulet );

    CharacterEquipmentItem ring() const;
    void setRing( const CharacterEquipmentItem& ring );

    CharacterEquipmentItem pickaxe() const;
    void setPickaxe( const CharacterEquipmentItem& pickaxe );

    CharacterEquipmentItem woodaxe() const;
    void setWoodaxe( const CharacterEquipmentItem& woodaxe );

    CharacterEquipmentItem fishrod() const;
    void setFishrod( const CharacterEquipmentItem& fishrod );

    CharacterEquipmentItem shovel() const;
    void setShovel( const CharacterEquipmentItem& shovel );

    CharacterEquipmentItem sickle() const;
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
