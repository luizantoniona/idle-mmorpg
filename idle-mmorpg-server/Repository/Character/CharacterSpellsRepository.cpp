#include "CharacterSpellsRepository.h"

#include <Commons/Singleton.h>
#include <Core/Manager/SpellManager.h>
#include <Database/Query.h>

namespace Repository {

CharacterSpellsRepository::CharacterSpellsRepository() :
    Repository() {}

bool CharacterSpellsRepository::createSpells( int idCharacter ) {
    return true;
}

bool CharacterSpellsRepository::updateSpells( int idCharacter, Model::CharacterSpells& characterSpells ) {
    const std::string upsertSql = R"SQL(
        INSERT INTO character_spells (id_character, id_spell)
        VALUES (?, ?)
        ON CONFLICT(id_character, id_spell) DO NOTHING
    )SQL";

    for ( auto& spell : characterSpells.healingSpells() ) {
        Database::Query query( _db, upsertSql );
        query.bindInt( 1, idCharacter );
        query.bindText( 2, spell.id() );

        if ( !query.exec() ) {
            return false;
        }
    }

    for ( auto& spell : characterSpells.attackSpells() ) {
        Database::Query query( _db, upsertSql );
        query.bindInt( 1, idCharacter );
        query.bindText( 2, spell.id() );

        if ( !query.exec() ) {
            return false;
        }
    }

    return true;
}

std::unique_ptr<Model::CharacterSpells> CharacterSpellsRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT id_spell
        FROM character_spells
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    auto characterSpells = std::make_unique<Model::CharacterSpells>();

    while ( query.step() ) {
        std::string spellId = query.getColumnText( 0 );

        auto spell = Commons::Singleton<Core::Manager::SpellManager>::instance().spellById( spellId );
        if ( spell ) {
            Model::CharacterSpell characterSpell;
            characterSpell.setId( spellId );
            characterSpell.setSpell( spell );
            characterSpell.setCount( spell->cooldown() );

            if ( spell->type() == "healing" ) {
                characterSpells->addHealingSpell( characterSpell );

            } else if ( spell->type() == "attack" ) {
                characterSpells->addAttackSpell( characterSpell );
            }
        }
    }

    return characterSpells;
}

} // namespace Repository
