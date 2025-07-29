#include "CharacterCoordinateRepository.h"

#include <Database/Query.h>

namespace Repository {

CharacterCoordinateRepository::CharacterCoordinateRepository() :
    Repository() {}

bool CharacterCoordinateRepository::createCoordinates( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_coordinates (
            id_character,
            x,
            y,
            z,
            x_spawn,
            y_spawn,
            z_spawn
        ) VALUES (?, 0, 0, 0, 0, 0, 0)
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idCharacter );
    return query.step();
}

bool CharacterCoordinateRepository::updateCoordinates( int idCharacter, const Model::CharacterCoordinates& coordinates ) {
    const std::string sql = R"SQL(
        UPDATE character_coordinates SET
            x = ?,
            y = ?,
            z = ?,
            x_spawn = ?,
            y_spawn = ?,
            z_spawn = ?
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, coordinates.x() );
    query.bindInt( 2, coordinates.y() );
    query.bindInt( 3, coordinates.z() );
    query.bindInt( 4, coordinates.xSpawn() );
    query.bindInt( 5, coordinates.ySpawn() );
    query.bindInt( 6, coordinates.zSpawn() );
    query.bindInt( 7, idCharacter );

    return query.step();
}

std::unique_ptr<Model::CharacterCoordinates> CharacterCoordinateRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            x,
            y,
            z,
            x_spawn,
            y_spawn,
            z_spawn
        FROM character_coordinates
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto coordinates = std::make_unique<Model::CharacterCoordinates>();
    coordinates->setX( query.getColumnInt( 0 ) );
    coordinates->setY( query.getColumnInt( 1 ) );
    coordinates->setZ( query.getColumnInt( 2 ) );
    coordinates->setXSpawn( query.getColumnInt( 3 ) );
    coordinates->setYSpawn( query.getColumnInt( 4 ) );
    coordinates->setZSpawn( query.getColumnInt( 5 ) );

    return coordinates;
}

} // namespace Repository
