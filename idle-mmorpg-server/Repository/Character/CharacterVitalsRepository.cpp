#include "CharacterVitalsRepository.h"

#include <Database/Query.h>

namespace Repository {

CharacterVitalsRepository::CharacterVitalsRepository() :
    Repository() {}

bool CharacterVitalsRepository::createVitals( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_vitals (
            id_character,
            health,
            max_health,
            mana,
            max_mana,
            stamina,
            max_stamina
        ) VALUES (?, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0)
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );
    return query.exec();
}

bool CharacterVitalsRepository::updateVitals( int idCharacter, const Model::CharacterVitals& vitals ) {
    const std::string sql = R"SQL(
        UPDATE character_vitals SET
            health = ?,
            max_health = ?,
            mana = ?,
            max_mana = ?,
            stamina = ?,
            max_stamina = ?
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindDouble( 1, vitals.health() );
    query.bindDouble( 2, vitals.maxHealth() );
    query.bindDouble( 3, vitals.mana() );
    query.bindDouble( 4, vitals.maxMana() );
    query.bindDouble( 5, vitals.stamina() );
    query.bindDouble( 6, vitals.maxStamina() );
    query.bindInt( 7, idCharacter );

    return query.exec();
}

std::unique_ptr<Model::CharacterVitals> CharacterVitalsRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            health,
            max_health,
            mana,
            max_mana,
            stamina,
            max_stamina
        FROM character_vitals
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto vitals = std::make_unique<Model::CharacterVitals>();
    vitals->setHealth( query.getColumnDouble( 0 ) );
    vitals->setMaxHealth( query.getColumnDouble( 1 ) );
    vitals->setMana( query.getColumnDouble( 2 ) );
    vitals->setMaxMana( query.getColumnDouble( 3 ) );
    vitals->setStamina( query.getColumnDouble( 4 ) );
    vitals->setMaxStamina( query.getColumnDouble( 5 ) );

    return vitals;
}

} // namespace Repository
