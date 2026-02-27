#include "CharacterStageRepository.h"

#include <Infrastructure/Database/Query.h>

namespace Repository {

CharacterStageRepository::CharacterStageRepository() :
    Repository() {
}

bool CharacterStageRepository::createStage( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_stage (
            id_character,
            id_stage,
            completed
        ) VALUES (?, 0, 0)
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    return query.exec();
}

bool CharacterStageRepository::updateStage( int idCharacter, const Domain::CharacterStage& stage ) {
    const std::string sql = R"SQL(
        UPDATE character_stage SET
            id_stage = ?,
            completed = ?
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, stage.stageLevel() );
    query.bindInt( 2, stage.completed() ? 1 : 0 );
    query.bindInt( 3, idCharacter );

    return query.exec();
}

std::unique_ptr<Domain::CharacterStage> CharacterStageRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            id_stage,
            completed
        FROM character_stage
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto stage = std::make_unique<Domain::CharacterStage>();
    stage->setStageLevel( query.getColumnInt( 0 ) );
    stage->setCompleted( query.getColumnInt( 1 ) != 0 );

    return stage;
}

} // namespace Repository
