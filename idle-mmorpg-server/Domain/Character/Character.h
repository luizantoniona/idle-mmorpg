#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include <json/json.h>

#include "CharacterActions.h"
#include "CharacterCombat.h"
#include "CharacterEffects.h"
#include "CharacterEquipment.h"
#include "CharacterInventory.h"
#include "CharacterProgression.h"
#include "CharacterSkills.h"
#include "CharacterSpells.h"
#include "CharacterStage.h"
#include "CharacterVitals.h"
#include "CharacterWallet.h"

namespace Domain {

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

    CharacterActions& actions();
    void setActions( const CharacterActions& actions );

    CharacterCombat& combat();
    void setCombat( const CharacterCombat& combat );

    CharacterEffects& effects();
    void setEffects( const CharacterEffects& effects );

    CharacterEquipment& equipment();
    void setEquipment( const CharacterEquipment& equipment );

    CharacterInventory& inventory();
    void setInventory( const CharacterInventory& inventory );

    CharacterProgression& progression();
    void setProgression( const CharacterProgression& progression );

    CharacterSkills& skills();
    void setSkills( const CharacterSkills& skills );

    CharacterSpells& spells();
    void setSpells( const CharacterSpells& spells );

    CharacterStage& stage();
    void setStage( const CharacterStage& stage );

    CharacterVitals& vitals();
    void setVitals( const CharacterVitals& vitals );

    CharacterWallet& wallet();
    void setWallet( const CharacterWallet& wallet );

private:
    int _idCharacter;
    int _idUser;
    std::string _name;

    CharacterActions _actions;
    CharacterCombat _combat;
    CharacterEffects _effects;
    CharacterEquipment _equipment;
    CharacterInventory _inventory;
    CharacterProgression _progression;
    CharacterSkills _skills;
    CharacterSpells _spells;
    CharacterStage _stage;
    CharacterVitals _vitals;
    CharacterWallet _wallet;
};

} // namespace Domain

#endif // CHARACTER_H
