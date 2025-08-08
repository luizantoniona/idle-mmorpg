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

    query.bindDouble( 1, attributes.baseStrength() );
    query.bindDouble( 2, attributes.baseDexterity() );
    query.bindDouble( 3, attributes.baseConstitution() );
    query.bindDouble( 4, attributes.baseIntelligence() );
    query.bindDouble( 5, attributes.baseWisdom() );
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
    attributes->setBaseStrength( query.getColumnDouble( 0 ) );
    attributes->setBaseDexterity( query.getColumnDouble( 1 ) );
    attributes->setBaseConstitution( query.getColumnDouble( 2 ) );
    attributes->setBaseIntelligence( query.getColumnDouble( 3 ) );
    attributes->setBaseWisdom( query.getColumnDouble( 4 ) );

    return attributes;
}

} // namespace Repository
