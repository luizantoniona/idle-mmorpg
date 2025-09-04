#include "CharacterAttributesRepository.h"

#include <Database/Query.h>

namespace Repository {

CharacterAttributesRepository::CharacterAttributesRepository() :
    Repository() {}

bool CharacterAttributesRepository::createAttributes( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_attributes (
            id_character,
            strength,
            dexterity,
            constitution,
            intelligence,
            wisdom
        ) VALUES (?, 0.0, 0.0, 0.0, 0.0, 0.0)
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idCharacter );
    return query.exec();
}

bool CharacterAttributesRepository::updateAttributes( int idCharacter, const Model::CharacterAttributes& attributes ) {
    const std::string sql = R"SQL(
        UPDATE character_attributes SET
            strength = ?,
            dexterity = ?,
            constitution = ?,
            intelligence = ?,
            wisdom = ?
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindDouble( 1, attributes.strength() );
    query.bindDouble( 2, attributes.dexterity() );
    query.bindDouble( 3, attributes.constitution() );
    query.bindDouble( 4, attributes.intelligence() );
    query.bindDouble( 5, attributes.wisdom() );
    query.bindInt( 6, idCharacter );

    return query.exec();
}

std::unique_ptr<Model::CharacterAttributes> CharacterAttributesRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            strength,
            dexterity,
            constitution,
            intelligence,
            wisdom
        FROM character_attributes
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto attributes = std::make_unique<Model::CharacterAttributes>();
    attributes->setStrength( query.getColumnDouble( 0 ) );
    attributes->setDexterity( query.getColumnDouble( 1 ) );
    attributes->setConstitution( query.getColumnDouble( 2 ) );
    attributes->setIntelligence( query.getColumnDouble( 3 ) );
    attributes->setWisdom( query.getColumnDouble( 4 ) );

    return attributes;
}

} // namespace Repository
