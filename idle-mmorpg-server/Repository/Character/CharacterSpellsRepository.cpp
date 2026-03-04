#include "CharacterSpellsRepository.h"

#include <Infrastructure/Database/Query.h>

namespace Repository {

CharacterSpellsRepository::CharacterSpellsRepository() :
    Repository() {}

bool CharacterSpellsRepository::createSpells( int idCharacter ) {
    return true;
}

bool CharacterSpellsRepository::updateSpells( int idCharacter, Domain::CharacterSpells& characterSpells ) {
    const std::string upsertSql = R"SQL(
        INSERT INTO character_spells (id_character, id_spell)
        VALUES (?, ?)
        ON CONFLICT(id_character, id_spell) DO NOTHING
    )SQL";

    for ( const auto& spell : characterSpells.spells() ) {
        Database::Query query( _db, upsertSql );
        query.bindInt( 1, idCharacter );
        query.bindText( 2, spell.id() );

        if ( !query.exec() ) {
            return false;
        }
    }

    return true;
}

std::unique_ptr<Domain::CharacterSpells> CharacterSpellsRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT id_spell
        FROM character_spells
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    auto characterSpells = std::make_unique<Domain::CharacterSpells>();

    while ( query.step() ) {
        Domain::CharacterSpell spell;
        spell.setId( query.getColumnText( 0 ) );
        characterSpells->addSpell( spell );
    }

    return characterSpells;
}

} // namespace Repository
