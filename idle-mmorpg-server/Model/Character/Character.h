#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include <json/json.h>

#include "CharacterAction.h"
#include "CharacterAttributes.h"
#include "CharacterCombatAction.h"
#include "CharacterCombatAttributes.h"
#include "CharacterCoordinates.h"
#include "CharacterEquipment.h"
#include "CharacterInventory.h"
#include "CharacterProgression.h"
#include "CharacterQuests.h"
#include "CharacterSkills.h"
#include "CharacterSpells.h"
#include "CharacterVitals.h"
#include "CharacterWallet.h"

namespace Model {

class Character {
public:
    Character();

    Json::Value toJson();

    int idCharacter() const;
    void setIdCharacter( int idCharacter );

    int idUser() const;
    void setIdUser( int idUser );

    std::string name() const;
    void setName( const std::string& name );

    CharacterAction& action();
    void setAction( const CharacterAction& action );

    CharacterAttributes& attributes();
    void setAttributes( const CharacterAttributes& attributes );

    CharacterCombatAction& combatAction();
    void setCombatAction( const CharacterCombatAction& combatAction );

    CharacterCombatAttributes& combatAttributes();
    void setCombatAttributes( const CharacterCombatAttributes& combatAttributes );

    CharacterCoordinates& coordinates();
    void setCoordinates( const CharacterCoordinates& coordinates );

    CharacterEquipment& equipment();
    void setEquipment( const CharacterEquipment& equipment );

    CharacterInventory& inventory();
    void setInventory( const CharacterInventory& inventory );

    CharacterProgression& progression();
    void setProgression( const CharacterProgression& progression );

    CharacterQuests& quests();
    void setQuests( const CharacterQuests& quests );

    CharacterSkills& skills();
    void setSkills( const CharacterSkills& skills );

    CharacterSpells& spells();
    void setSpells( const CharacterSpells& spells );

    CharacterVitals& vitals();
    void setVitals( const CharacterVitals& vitals );

    CharacterWallet& wallet();
    void setWallet( const CharacterWallet& wallet );

private:
    int _idCharacter;
    int _idUser;
    std::string _name;
    CharacterAction _action;
    CharacterAttributes _attributes;
    CharacterCombatAction _combatAction;
    CharacterCombatAttributes _combatAttributes;
    CharacterCoordinates _coordinates;
    CharacterEquipment _equipment;
    CharacterInventory _inventory;
    CharacterProgression _progression;
    CharacterQuests _quests;
    CharacterSkills _skills;
    CharacterSpells _spells;
    CharacterVitals _vitals;
    CharacterWallet _wallet;
};

} // namespace Model

#endif // CHARACTER_H
