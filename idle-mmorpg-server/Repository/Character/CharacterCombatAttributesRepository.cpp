#include "CharacterCombatAttributesRepository.h"

#include <Database/Query.h>

namespace Repository {

CharacterCombatAttributesRepository::CharacterCombatAttributesRepository() :
    Repository() {
}

bool CharacterCombatAttributesRepository::createAttributes( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_combat_attributes (
            id_character,
            attack,
            accuracy,
            defense,
            speed,
            evasion,
            critical_chance,
            critical_multiplier
        ) VALUES (?, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0)
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idCharacter );
    return query.exec();
}

bool CharacterCombatAttributesRepository::updateAttributes( int idCharacter, const Model::CharacterCombatAttributes& attributes ) {
    const std::string sql = R"SQL(
        UPDATE character_combat_attributes SET
            attack = ?,
            accuracy = ?,
            defense = ?,
            speed = ?,
            evasion = ?,
            critical_chance = ?,
            critical_multiplier = ?
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindDouble( 1, attributes.baseAttack() );
    query.bindDouble( 2, attributes.baseAccuracy() );
    query.bindDouble( 3, attributes.baseDefense() );
    query.bindDouble( 4, attributes.baseSpeed() );
    query.bindDouble( 5, attributes.baseEvasion() );
    query.bindDouble( 6, attributes.baseCriticalChance() );
    query.bindDouble( 7, attributes.baseCriticalMultiplier() );
    query.bindInt( 8, idCharacter );

    return query.exec();
}

std::unique_ptr<Model::CharacterCombatAttributes> CharacterCombatAttributesRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            attack,
            accuracy,
            defense,
            speed,
            evasion,
            critical_chance,
            critical_multiplier
        FROM character_combat_attributes
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto attributes = std::make_unique<Model::CharacterCombatAttributes>();
    attributes->setBaseAttack( query.getColumnDouble( 0 ) );
    attributes->setBaseAccuracy( query.getColumnDouble( 1 ) );
    attributes->setBaseDefense( query.getColumnDouble( 2 ) );
    attributes->setBaseSpeed( query.getColumnDouble( 3 ) );
    attributes->setBaseEvasion( query.getColumnDouble( 4 ) );
    attributes->setBaseCriticalChance( query.getColumnDouble( 5 ) );
    attributes->setBaseCriticalMultiplier( query.getColumnDouble( 6 ) );

    return attributes;
}

} // namespace Repository
