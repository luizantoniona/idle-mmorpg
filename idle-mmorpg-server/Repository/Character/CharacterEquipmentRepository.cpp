#include "CharacterEquipmentRepository.h"

#include <Commons/Singleton.h>
#include <Core/Manager/ItemManager.h>
#include <Database/Query.h>
#include <Model/Character/CharacterEquipmentItem.h>

namespace Repository {

CharacterEquipmentRepository::CharacterEquipmentRepository() :
    Repository() {
}

bool CharacterEquipmentRepository::createEquipment( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_equipment (
            id_character,
            head_item_id,
            chest_item_id,
            legs_item_id,
            boots_item_id,
            gloves_item_id,
            left_hand_item_id,
            right_hand_item_id,
            amulet_item_id,
            ring_item_id
        ) VALUES (?, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );
    return query.step();
}

bool CharacterEquipmentRepository::updateEquipment( int idCharacter, const Model::CharacterEquipment& equipment ) {
    const std::string sql = R"SQL(
        UPDATE character_equipment SET
            head_item_id = ?,
            chest_item_id = ?,
            legs_item_id = ?,
            boots_item_id = ?,
            gloves_item_id = ?,
            left_hand_item_id = ?,
            right_hand_item_id = ?,
            amulet_item_id = ?,
            ring_item_id = ?
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindText( 1, equipment.head().id() );
    query.bindText( 2, equipment.chest().id() );
    query.bindText( 3, equipment.legs().id() );
    query.bindText( 4, equipment.boots().id() );
    query.bindText( 5, equipment.gloves().id() );
    query.bindText( 6, equipment.leftHand().id() );
    query.bindText( 7, equipment.rightHand().id() );
    query.bindText( 8, equipment.amulet().id() );
    query.bindText( 9, equipment.ring().id() );
    query.bindInt( 10, idCharacter );

    return query.step();
}

std::unique_ptr<Model::CharacterEquipment> CharacterEquipmentRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            head_item_id,
            chest_item_id,
            legs_item_id,
            boots_item_id,
            gloves_item_id,
            left_hand_item_id,
            right_hand_item_id,
            amulet_item_id,
            ring_item_id
        FROM character_equipment
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto& manager = Commons::Singleton<Core::Manager::ItemManager>::instance();
    auto equipment = std::make_unique<Model::CharacterEquipment>();

    auto makeItem = [ & ]( const std::string& id ) {
        Model::CharacterEquipmentItem item;
        item.setId( id );
        item.setItem( manager.itemById( id ) );
        return item;
    };

    equipment->setHead( makeItem( query.getColumnText( 0 ) ) );
    equipment->setChest( makeItem( query.getColumnText( 1 ) ) );
    equipment->setLegs( makeItem( query.getColumnText( 2 ) ) );
    equipment->setBoots( makeItem( query.getColumnText( 3 ) ) );
    equipment->setGloves( makeItem( query.getColumnText( 4 ) ) );
    equipment->setLeftHand( makeItem( query.getColumnText( 5 ) ) );
    equipment->setRightHand( makeItem( query.getColumnText( 6 ) ) );
    equipment->setAmulet( makeItem( query.getColumnText( 7 ) ) );
    equipment->setRing( makeItem( query.getColumnText( 8 ) ) );

    return equipment;
}

} // namespace Repository
