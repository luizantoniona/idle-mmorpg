#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include <json/json.h>

#include "CharacterAction.h"
#include "CharacterVitals.h"

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

    std::string sessionId() const;
    void setSessionId( const std::string& sessionId );

    CharacterAction& action();
    void setAction( const CharacterAction& action );

    CharacterVitals& vitals();
    void setVitals( const CharacterVitals& vitals );

    /*CharacterCombatAction& combatAction();
    void setCombatAction( const CharacterCombatAction& combatAction );

    CharacterCombatAttributes& combatAttributes();
    void setCombatAttributes( const CharacterCombatAttributes& combatAttributes );

    CharacterCoordinates& coordinates();
    void setCoordinates( const CharacterCoordinates& coordinates );

    CharacterEffects& effects();
    void setEffects( const CharacterEffects& effects );

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
    void setWallet( const CharacterWallet& wallet );*/

private:
    int _idCharacter;
    int _idUser;
    std::string _name;
    std::string _sessionId;
    CharacterAction _action;
    CharacterVitals _vitals;
    /*CharacterCombatAction _combatAction;
    CharacterCombatAttributes _combatAttributes;
    CharacterCoordinates _coordinates;
    CharacterEffects _effects;
    CharacterEquipment _equipment;
    CharacterInventory _inventory;
    CharacterProgression _progression;
    CharacterQuests _quests;
    CharacterSkills _skills;
    CharacterSpells _spells;
    CharacterWallet _wallet;*/
};

} // namespace Domain

#endif // CHARACTER_H
