#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

#include <json/json.h>

#include "CharacterAttributes.h"
#include "CharacterCoordinates.h"
#include "CharacterInventory.h"
#include "CharacterSkills.h"
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

    std::string dsName() const;
    void setDsName( const std::string& dsName );

    CharacterAttributes& attributes();
    void setAttributes( const CharacterAttributes& attributes );

    CharacterCoordinates& coordinates();
    void setCoordinates( const CharacterCoordinates& coordinates );

    CharacterInventory& inventory();
    void setInventory( const CharacterInventory& inventory );

    CharacterSkills& skills();
    void setSkills( const CharacterSkills& skills );

    CharacterWallet& wallet();
    void setWallet( const CharacterWallet& wallet );

private:
    int _idCharacter;
    int _idUser;
    std::string _dsName;
    CharacterAttributes _attributes;
    CharacterCoordinates _coordinates;
    CharacterInventory _inventory;
    CharacterSkills _skills;
    CharacterWallet _wallet;
};

} // namespace Model

#endif // CHARACTER_H
