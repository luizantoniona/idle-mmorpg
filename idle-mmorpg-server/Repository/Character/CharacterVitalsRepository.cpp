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
            base_health_regen,
            mana,
            max_mana,
            base_mana_regen,
            stamina,
            max_stamina,
            base_stamina_regen
        ) VALUES (?, 10.0, 10.0, 0.0, 10.0, 10.0, 0.0, 10.0, 10.0, 0.0)
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );
    return query.step();
}

bool CharacterVitalsRepository::updateVitals( int idCharacter, const Model::CharacterVitals& vitals ) {
    const std::string sql = R"SQL(
        UPDATE character_vitals SET
            health = ?,
            max_health = ?,
            base_health_regen = ?,
            mana = ?,
            max_mana = ?,
            base_mana_regen = ?,
            stamina = ?,
            max_stamina = ?,
            base_stamina_regen = ?
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindDouble( 1, vitals.health() );
    query.bindDouble( 2, vitals.maxHealth() );
    query.bindDouble( 3, vitals.baseHealthRegen() );
    query.bindDouble( 4, vitals.mana() );
    query.bindDouble( 5, vitals.maxMana() );
    query.bindDouble( 6, vitals.baseManaRegen() );
    query.bindDouble( 7, vitals.stamina() );
    query.bindDouble( 8, vitals.maxStamina() );
    query.bindDouble( 9, vitals.baseStaminaRegen() );
    query.bindInt( 10, idCharacter );

    return query.step();
}

std::unique_ptr<Model::CharacterVitals> CharacterVitalsRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            health,
            max_health,
            base_health_regen,
            mana,
            max_mana,
            base_mana_regen,
            stamina,
            max_stamina,
            base_stamina_regen
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
    vitals->setBaseHealthRegen( query.getColumnDouble( 2 ) );
    vitals->setMana( query.getColumnDouble( 3 ) );
    vitals->setMaxMana( query.getColumnDouble( 4 ) );
    vitals->setBaseManaRegen( query.getColumnDouble( 5 ) );
    vitals->setStamina( query.getColumnDouble( 6 ) );
    vitals->setMaxStamina( query.getColumnDouble( 7 ) );
    vitals->setBaseStaminaRegen( query.getColumnDouble( 8 ) );

    return vitals;
}

} // namespace Repository
