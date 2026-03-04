#include "CharacterInventoryRepository.h"

#include <Infrastructure/Database/Query.h>

namespace Repository {

CharacterInventoryRepository::CharacterInventoryRepository() :
    Repository() {}

bool CharacterInventoryRepository::createInventory( int idCharacter ) {
    return true;
}

bool CharacterInventoryRepository::updateInventory( int idCharacter, Domain::CharacterInventory& inventory ) {
    const std::string deleteSql = R"SQL(
        DELETE FROM character_inventory
        WHERE id_character = ?
    )SQL";

    Database::Query deleteQuery( _db, deleteSql );
    deleteQuery.bindInt( 1, idCharacter );

    if ( !deleteQuery.exec() ) {
        return false;
    }

    const std::string insertSql = R"SQL(
        INSERT INTO character_inventory (id_character, id_item, amount)
        VALUES (?, ?, ?)
    )SQL";

    for ( Domain::CharacterInventoryItem& item : inventory.items() ) {
        Database::Query insertQuery( _db, insertSql );
        insertQuery.bindInt( 1, idCharacter );
        insertQuery.bindText( 2, item.id() );
        insertQuery.bindInt( 3, item.amount() );

        if ( !insertQuery.exec() ) {
            return false;
        }
    }

    return true;
}

std::unique_ptr<Domain::CharacterInventory> CharacterInventoryRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT id_item, amount
        FROM character_inventory
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    auto inventory = std::make_unique<Domain::CharacterInventory>();

    while ( query.step() ) {
        Domain::CharacterInventoryItem inventoryItem;
        inventoryItem.setId( query.getColumnText( 0 ) );
        inventoryItem.setAmount( query.getColumnInt( 1 ) );

        inventory->addItem( inventoryItem );
    }

    return inventory;
}

} // namespace Repository
