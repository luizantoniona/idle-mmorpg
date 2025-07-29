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
            wisdom,
            charisma
        ) VALUES (?, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0)
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idCharacter );
    return query.step();
}

bool CharacterAttributesRepository::updateAttributes( int idCharacter, const Model::CharacterAttributes& attributes ) {
    const std::string sql = R"SQL(
        UPDATE character_attributes SET
            strength = ?,
            dexterity = ?,
            constitution = ?,
            intelligence = ?,
            wisdom = ?,
            charisma = ?
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindDouble( 1, attributes.baseStrength() );
    query.bindDouble( 2, attributes.baseDexterity() );
    query.bindDouble( 3, attributes.baseConstitution() );
    query.bindDouble( 4, attributes.baseIntelligence() );
    query.bindDouble( 5, attributes.baseWisdom() );
    query.bindDouble( 6, attributes.baseCharisma() );
    query.bindInt( 7, idCharacter );

    return query.step();
}

std::unique_ptr<Model::CharacterAttributes> CharacterAttributesRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            strength,
            dexterity,
            constitution,
            intelligence,
            wisdom,
            charisma
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
    attributes->setBaseCharisma( query.getColumnDouble( 5 ) );

    return attributes;
}

} // namespace Repository
