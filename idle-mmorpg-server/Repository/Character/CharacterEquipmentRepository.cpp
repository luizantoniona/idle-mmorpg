#include "CharacterEquipmentRepository.h"

#include <Commons/Singleton.h>
#include <Core/Manager/ItemManager.h>
#include <Database/Query.h>
#include <Model/Character/CharacterEquipmentItem.h>

namespace Repository {

CharacterEquipmentRepository::CharacterEquipmentRepository() :
    Repository() {}

bool CharacterEquipmentRepository::createEquipment( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_equipment (id_character) VALUES (?)
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );
    return query.exec();
}

bool CharacterEquipmentRepository::updateEquipment( int idCharacter, const Model::CharacterEquipment& equipment ) {
    const std::string sql = R"SQL(
        UPDATE character_equipment SET
            helmet_item_id = ?,
            armor_item_id = ?,
            leg_item_id = ?,
            boot_item_id = ?,
            glove_item_id = ?,
            left_hand_item_id = ?,
            right_hand_item_id = ?,
            amulet_item_id = ?,
            ring_item_id = ?,
            pickaxe_item_id = ?,
            woodaxe_item_id = ?,
            fishrod_item_id = ?,
            shovel_item_id = ?,
            sickle_item_id = ?
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindText( 1, equipment.helmet().id() );
    query.bindText( 2, equipment.armor().id() );
    query.bindText( 3, equipment.leg().id() );
    query.bindText( 4, equipment.boot().id() );
    query.bindText( 5, equipment.glove().id() );
    query.bindText( 6, equipment.leftHand().id() );
    query.bindText( 7, equipment.rightHand().id() );
    query.bindText( 8, equipment.amulet().id() );
    query.bindText( 9, equipment.ring().id() );
    query.bindText( 10, equipment.pickaxe().id() );
    query.bindText( 11, equipment.woodaxe().id() );
    query.bindText( 12, equipment.fishrod().id() );
    query.bindText( 13, equipment.shovel().id() );
    query.bindText( 14, equipment.sickle().id() );
    query.bindInt( 15, idCharacter );

    return query.exec();
}

std::unique_ptr<Model::CharacterEquipment> CharacterEquipmentRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            helmet_item_id,
            armor_item_id,
            leg_item_id,
            boot_item_id,
            glove_item_id,
            left_hand_item_id,
            right_hand_item_id,
            amulet_item_id,
            ring_item_id,
            pickaxe_item_id,
            woodaxe_item_id,
            fishrod_item_id,
            shovel_item_id,
            sickle_item_id
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

    auto makeItem = [&]( const std::string& id ) {
                        Model::CharacterEquipmentItem item;
                        item.setId( id );
                        item.setItem( manager.itemById( id ) );
                        return item;
                    };

    equipment->setHelmet( makeItem( query.getColumnText( 0 ) ) );
    equipment->setArmor( makeItem( query.getColumnText( 1 ) ) );
    equipment->setLeg( makeItem( query.getColumnText( 2 ) ) );
    equipment->setBoot( makeItem( query.getColumnText( 3 ) ) );
    equipment->setGlove( makeItem( query.getColumnText( 4 ) ) );
    equipment->setLeftHand( makeItem( query.getColumnText( 5 ) ) );
    equipment->setRightHand( makeItem( query.getColumnText( 6 ) ) );
    equipment->setAmulet( makeItem( query.getColumnText( 7 ) ) );
    equipment->setRing( makeItem( query.getColumnText( 8 ) ) );
    equipment->setPickaxe( makeItem( query.getColumnText( 9 ) ) );
    equipment->setWoodaxe( makeItem( query.getColumnText( 10 ) ) );
    equipment->setFishrod( makeItem( query.getColumnText( 11 ) ) );
    equipment->setShovel( makeItem( query.getColumnText( 12 ) ) );
    equipment->setSickle( makeItem( query.getColumnText( 13 ) ) );

    return equipment;
}

} // namespace Repository
