#include "CharacterCoordinateRepository.h"

#include <Infrastructure/Database/Query.h>

namespace Repository {

CharacterCoordinateRepository::CharacterCoordinateRepository() :
    Repository() {}

bool CharacterCoordinateRepository::createCoordinates( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_coordinates (
            id_character,
            location_id,
            structure_id,
            spawn_location_id,
            spawn_structure_id
        ) VALUES (?, '', NULL, '', NULL)
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idCharacter );
    return query.exec();
}

bool CharacterCoordinateRepository::updateCoordinates(
    int idCharacter, const Domain::CharacterCoordinates& coordinates ) {
    const std::string sql = R"SQL(
        UPDATE character_coordinates SET
            location_id = ?,
            structure_id = ?,
            spawn_location_id = ?,
            spawn_structure_id = ?
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindText( 1, coordinates.locationId() );
    query.bindText( 2, coordinates.structureId() );
    query.bindText( 3, coordinates.spawnLocationId() );
    query.bindText( 4, coordinates.spawnStructureId() );
    query.bindInt( 5, idCharacter );

    return query.exec();
}

std::unique_ptr<Domain::CharacterCoordinates> CharacterCoordinateRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            location_id,
            structure_id,
            spawn_location_id,
            spawn_structure_id
        FROM character_coordinates
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );

    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto coordinates = std::make_unique<Domain::CharacterCoordinates>();
    coordinates->setLocationId( query.getColumnText( 0 ) );
    coordinates->setStructureId( query.getColumnText( 1 ) );
    coordinates->setSpawnLocationId( query.getColumnText( 2 ) );
    coordinates->setSpawnStructureId( query.getColumnText( 3 ) );

    return coordinates;
}

} // namespace Repository
