#include "CharacterRepository.h"

#include <Database/Query.h>

#include "CharacterAttributesRepository.h"
#include "CharacterCoordinateRepository.h"
#include "CharacterInventoryRepository.h"
#include "CharacterSkillsRepository.h"
#include "CharacterWalletRepository.h"

namespace Repository {

CharacterRepository::CharacterRepository() :
    Repository() {}

bool CharacterRepository::createCharacter( const int idUser, const std::string& dsName ) {
    const std::string sql = R"SQL(
        INSERT INTO character (
            id_user,
            ds_name
        ) VALUES (?, ?)
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idUser );
    query.bindText( 2, dsName );

    if ( !query.step() ) {
        return false;
    }

    int idCharacter = static_cast<int>( sqlite3_last_insert_rowid( _db ) );

    const bool successAttributes = CharacterAttributesRepository().createAttributes( idCharacter );
    const bool successCoordinates = CharacterCoordinateRepository().createCoordinates( idCharacter );
    const bool succesWallet = CharacterWalletRepository().createWallet( idCharacter );
    const bool succesSkill = CharacterSkillsRepository().createSkills( idCharacter );
    const bool sucessInventory = CharacterInventoryRepository().createInventory( idCharacter );

    return successAttributes && successCoordinates && sucessInventory && succesWallet && succesSkill;
}

std::vector<std::unique_ptr<Model::Character> > CharacterRepository::findAllByIdUser( const int idUser ) {
    const std::string sql = R"SQL(
        SELECT
            id_character,
            id_user,
            ds_name
        FROM character
        WHERE id_user = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idUser );

    std::vector<std::unique_ptr<Model::Character> > characters;

    // TODO: Review this method, as it is only for the account page. So we don't need to load all data from character;

    while ( query.step() ) {
        auto character = std::make_unique<Model::Character>();
        character->setIdCharacter( query.getColumnInt( 0 ) );
        character->setIdUser( query.getColumnInt( 1 ) );
        character->setName( query.getColumnText( 2 ) );

        auto attributes = CharacterAttributesRepository().findByCharacterId( character->idCharacter() );
        if ( attributes ) {
            character->setAttributes( *attributes );
        }

        auto coordinates = CharacterCoordinateRepository().findByCharacterId( character->idCharacter() );
        if ( coordinates ) {
            character->setCoordinates( *coordinates );
        }

//        auto inventory = CharacterInventoryRepository().findByCharacterId( character->idCharacter() );
//        if ( inventory ) {
//            character->setInventory( *inventory );
//        }

        auto skills = CharacterSkillsRepository().findByCharacterId( character->idCharacter() );
        if ( skills ) {
            character->setSkills( *skills );
        }

        auto wallet = CharacterWalletRepository().findByCharacterId( character->idCharacter() );
        if ( coordinates ) {
            character->setWallet( *wallet );
        }

        characters.push_back( std::move( character ) );
    }

    return characters;
}

std::unique_ptr<Model::Character> CharacterRepository::findByIdUserAndIdCharacter( const int idUser, const int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            id_character,
            id_user,
            ds_name
        FROM character
        WHERE id_user = ? AND id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idUser );
    query.bindInt( 2, idCharacter );

    if ( query.step() ) {
        auto character = std::make_unique<Model::Character>();
        character->setIdCharacter( query.getColumnInt( 0 ) );
        character->setIdUser( query.getColumnInt( 1 ) );
        character->setName( query.getColumnText( 2 ) );

        auto attributes = CharacterAttributesRepository().findByCharacterId( character->idCharacter() );
        if ( attributes ) {
            character->setAttributes( *attributes );
        }

        auto coordinates = CharacterCoordinateRepository().findByCharacterId( character->idCharacter() );
        if ( coordinates ) {
            character->setCoordinates( *coordinates );
        }

//        auto inventory = CharacterInventoryRepository().findByCharacterId( character->idCharacter() );
//        if ( inventory ) {
//            character->setInventory( *inventory );
//        }

        auto skills = CharacterSkillsRepository().findByCharacterId( character->idCharacter() );
        if ( skills ) {
            character->setSkills( *skills );
        }

        auto wallet = CharacterWalletRepository().findByCharacterId( character->idCharacter() );
        if ( coordinates ) {
            character->setWallet( *wallet );
        }

        return character;
    }

    return nullptr;
}

} // namespace Repository
