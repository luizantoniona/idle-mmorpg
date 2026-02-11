#include "CharacterEquipmentRepository.h"

#include <Domain/Character/CharacterEquipmentItem.h>
#include <Infrastructure/Database/Query.h>

namespace Repository {

CharacterEquipmentRepository::CharacterEquipmentRepository() :
    Repository() {}

bool CharacterEquipmentRepository::createEquipment( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_equipment (id_character)
        VALUES (?)
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );
    return query.exec();
}

bool CharacterEquipmentRepository::updateEquipment( int idCharacter, Domain::CharacterEquipment& equipment ) {
    const std::string sql = R"SQL(
        UPDATE character_equipment SET
            helmet_item_id = ?,
            armor_item_id = ?,
            leg_item_id = ?,
            boot_item_id = ?,
            weapon_item_id = ?,
            offhand_item_id = ?,
            amulet_item_id = ?,
            ring_item_id = ?,
            pickaxe_item_id = ?,
            woodaxe_item_id = ?,
            fishingrod_item_id = ?,
            sickle_item_id = ?
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindText( 1, equipment.helmet().id() );
    query.bindText( 2, equipment.armor().id() );
    query.bindText( 3, equipment.leg().id() );
    query.bindText( 4, equipment.boot().id() );
    query.bindText( 5, equipment.weapon().id() );
    query.bindText( 6, equipment.offhand().id() );
    query.bindText( 7, equipment.amulet().id() );
    query.bindText( 8, equipment.ring().id() );
    query.bindText( 9, equipment.pickaxe().id() );
    query.bindText( 10, equipment.woodaxe().id() );
    query.bindText( 11, equipment.fishingrod().id() );
    query.bindText( 12, equipment.sickle().id() );
    query.bindInt( 13, idCharacter );

    return query.exec();
}

std::unique_ptr<Domain::CharacterEquipment> CharacterEquipmentRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT
            helmet_item_id,
            armor_item_id,
            leg_item_id,
            boot_item_id,
            weapon_item_id,
            offhand_item_id,
            amulet_item_id,
            ring_item_id,
            pickaxe_item_id,
            woodaxe_item_id,
            fishingrod_item_id,
            sickle_item_id
        FROM character_equipment
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto equipment = std::make_unique<Domain::CharacterEquipment>();

    Domain::CharacterEquipmentItem item;

    item.setId( query.getColumnText( 0 ) );
    equipment->setHelmet( item );

    item.setId( query.getColumnText( 1 ) );
    equipment->setArmor( item );

    item.setId( query.getColumnText( 2 ) );
    equipment->setLeg( item );

    item.setId( query.getColumnText( 3 ) );
    equipment->setBoot( item );

    item.setId( query.getColumnText( 4 ) );
    equipment->setWeapon( item );

    item.setId( query.getColumnText( 5 ) );
    equipment->setOffhand( item );

    item.setId( query.getColumnText( 6 ) );
    equipment->setAmulet( item );

    item.setId( query.getColumnText( 7 ) );
    equipment->setRing( item );

    item.setId( query.getColumnText( 8 ) );
    equipment->setPickaxe( item );

    item.setId( query.getColumnText( 9 ) );
    equipment->setWoodaxe( item );

    item.setId( query.getColumnText( 10 ) );
    equipment->setFishingrod( item );

    item.setId( query.getColumnText( 11 ) );
    equipment->setSickle( item );

    return equipment;
}

} // namespace Repository
