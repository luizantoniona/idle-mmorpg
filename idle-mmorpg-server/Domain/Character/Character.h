#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include <json/json.h>

#include "CharacterEquipment.h"
#include "CharacterInventory.h"
#include "CharacterProgression.h"
#include "CharacterSkills.h"
#include "CharacterSpells.h"
#include "CharacterStage.h"
#include "CharacterVitals.h"
#include "CharacterWallet.h"

#include "CharacterActions.h"
#include "CharacterEffects.h"

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

    // --- Persistent Data
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

    // --- Runtime Data
    CharacterActions& actions();
    void setActions( const CharacterActions& actions );

    CharacterEffects& effects();
    void setEffects( const CharacterEffects& effects );

private:
    int _idCharacter;
    int _idUser;
    std::string _name;

    // --- Persistent Data
    CharacterEquipment _equipment;
    CharacterInventory _inventory;
    CharacterProgression _progression;
    CharacterSkills _skills;
    CharacterSpells _spells;
    CharacterStage _stage;
    CharacterVitals _vitals;
    CharacterWallet _wallet;

    // --- Runtime Data
    CharacterActions _actions;
    CharacterEffects _effects;
};

} // namespace Domain

#endif // CHARACTER_H
