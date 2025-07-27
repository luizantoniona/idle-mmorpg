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

//bool CharacterInventoryRepository::updateCharacterInventory( int idCharacter, const Model::CharacterInventoryModel& inventory ) {
//    const std::string deleteSql = R"SQL(
//        DELETE FROM character_inventory WHERE id_character = ?
//    )SQL";

//    Database::Query deleteQuery( _db, deleteSql );
//    deleteQuery.bindInt( 1, idCharacter );

//    if ( !deleteQuery.step() ) {
//        return false;
//    }

//    const std::string insertSql = R"SQL(
//        INSERT INTO character_inventory (id_character, id_item, amount) VALUES (?, ?, ?)
//    )SQL";

//    for ( const auto& [ idItem, amount ] : inventory.items() ) {
//        Database::Query insertQuery( _db, insertSql );
//        insertQuery.bindInt( 1, idCharacter );
//        insertQuery.bindInt( 2, idItem );
//        insertQuery.bindInt( 3, amount );

//        if ( !insertQuery.step() ) {
//            return false;
//        }
//    }

//    return true;
//}

//std::unique_ptr<Model::CharacterInventoryModel> CharacterInventoryRepository::findByCharacterId( int idCharacter ) {
//    const std::string sql = R"SQL(
//        SELECT id_item, amount FROM character_inventory WHERE id_character = ?
//    )SQL";

//    Database::Query query( _db, sql );
//    query.bindInt( 1, idCharacter );

//    auto inventory = std::make_unique<Model::CharacterInventoryModel>();

//    while ( query.step() ) {
//        std::string idItem = query.getColumnText( 0 );
//        int amount = query.getColumnInt( 1 );
//        inventory->addItem( idItem, amount );
//        // TODO Remove the setItemModel from here
//        inventory->setItemModel( idItem, Commons::Singleton<System::Manager::ItemManager>::instance().itemById( idItem ) );
//    }

//    return inventory;
//}

} // namespace Repository
