#include "CharacterInventoryRepository.h"

#include <Commons/Singleton.h>
#include <Core/Manager/ItemManager.h>
#include <Database/Query.h>

namespace Repository {

CharacterInventoryRepository::CharacterInventoryRepository() :
    Repository() {}

bool CharacterInventoryRepository::createInventory( int idCharacter ) {
    return true;
}

bool CharacterInventoryRepository::updateInventory( int idCharacter, Model::CharacterInventory& inventory ) {
    const std::string deleteSql = R"SQL(
        DELETE FROM character_inventory WHERE id_character = ?
    )SQL";

    Database::Query deleteQuery( _db, deleteSql );
    deleteQuery.bindInt( 1, idCharacter );

    if ( !deleteQuery.exec() ) {
        return false;
    }

    const std::string insertSql = R"SQL(
        INSERT INTO character_inventory (id_character, id_item, amount) VALUES (?, ?, ?)
    )SQL";

    for ( Model::CharacterInventoryItem& item : inventory.items() ) {
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

std::unique_ptr<Model::CharacterInventory> CharacterInventoryRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT id_item, amount FROM character_inventory WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    auto inventory = std::make_unique<Model::CharacterInventory>();

    auto& itemManager = Commons::Singleton<Core::Manager::ItemManager>::instance();

    while ( query.step() ) {
        std::string idItem = query.getColumnText( 0 );
        int amount = query.getColumnInt( 1 );

        Model::CharacterInventoryItem inventoryItem;
        inventoryItem.setId( idItem );
        inventoryItem.setAmount( amount );
        inventoryItem.setItem( itemManager.itemById( idItem ) );

        inventory->addItem( inventoryItem );
    }

    return inventory;
}

} // namespace Repository
