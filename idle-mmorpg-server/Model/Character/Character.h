#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include <json/json.h>

#include "CharacterAction.h"
#include "CharacterAttributes.h"
#include "CharacterCoordinates.h"
#include "CharacterInventory.h"
#include "CharacterProgression.h"
#include "CharacterSkills.h"
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

    CharacterCoordinates& coordinates();
    void setCoordinates( const CharacterCoordinates& coordinates );

    CharacterInventory& inventory();
    void setInventory( const CharacterInventory& inventory );

    CharacterProgression& progression();
    void setProgression( const CharacterProgression& progression );

    CharacterSkills& skills();
    void setSkills( const CharacterSkills& skills );

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
    CharacterCoordinates _coordinates;
    CharacterInventory _inventory;
    CharacterProgression _progression;
    CharacterSkills _skills;
    CharacterVitals _vitals;
    CharacterWallet _wallet;
};

} // namespace Model

#endif // CHARACTER_H
