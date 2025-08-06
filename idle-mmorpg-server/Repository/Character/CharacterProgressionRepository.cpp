#include "CharacterProgressionRepository.h"

#include <Database/Query.h>

namespace Repository {

CharacterProgressionRepository::CharacterProgressionRepository() :
    Repository() {}

bool CharacterProgressionRepository::createProgression( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_progression (
            id_character,
            level,
            experience
        ) VALUES (?, 0, 0)
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );
    return query.exec();
}

bool CharacterProgressionRepository::updateProgression( int idCharacter, const Model::CharacterProgression& progression ) {
    const std::string sql = R"SQL(
        UPDATE character_progression SET
            level = ?,
            experience = ?
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, progression.level() );
    query.bindInt( 2, progression.experience() );
    query.bindInt( 3, idCharacter );

    return query.exec();
}

std::unique_ptr<Model::CharacterProgression> CharacterProgressionRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            level,
            experience
        FROM character_progression
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto progression = std::make_unique<Model::CharacterProgression>();
    progression->setLevel( query.getColumnInt( 0 ) );
    progression->setExperience( query.getColumnInt( 1 ) );

    return progression;
}

} // namespace Repository
