#include "ItemSystem.h"

#include <iostream>

#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

#include "NotificationSystem.h"
#include "QuestSystem.h"

namespace Core::System {

void ItemSystem::characterUseItem( const std::string& sessionId, Model::Character* character, const Json::Value& payload ) {
    const std::string itemId = payload[ "itemId" ].asString();

    if ( !itemId.empty() ) {

        auto& inventory = character->inventory();

        if ( !inventory.hasItem( itemId, 1 ) ) {
            std::cerr << "ItemSystem::characterUseItem item not found in inventory: " << itemId << std::endl;
            return;
        }

        const Model::CharacterInventoryItem* itemToUse = inventory.itemById( itemId );

        if ( itemToUse->item()->type() != "consumable" ) {
            std::cerr << "ItemSystem::characterUseItem item is not consumable: " << itemId << std::endl;
            return;
        }

        for ( const Model::ItemEffect& itemEffect : itemToUse->item()->effects() ) {
            Model::CharacterEffect effect;
            effect.setSource( itemToUse->id() );
            effect.setSourceName( itemToUse->item()->name() );
            effect.setType( itemEffect.type() );
            effect.setCategory( itemEffect.category() );
            effect.setValue( itemEffect.value() );
            effect.setDuration( itemEffect.duration() );
            effect.setCounter( 0 );
            character->effects().addEffect( effect );
        }

        inventory.removeItem( itemId, 1 );
    }

    QuestSystem::updateItemQuest( sessionId, character );
    NotificationSystem::notifyCharacterInventory( sessionId, character );
    NotificationSystem::notifyCharacterEffects( sessionId, character );
}

void ItemSystem::characterEquipItem( const std::string& sessionId, Model::Character* character, const Json::Value& payload ) {
    const std::string itemId = payload[ "itemId" ].asString();
    const std::string slot = payload[ "slot" ].asString();

    auto& characterInventory = character->inventory();
    auto& characterEquipments = character->equipment();

    std::unordered_map<std::string, Model::CharacterEquipmentItem&> slotMap = {
        { "helmet", characterEquipments.helmet() },
        { "armor", characterEquipments.armor() },
        { "leg", characterEquipments.leg() },
        { "boot", characterEquipments.boot() },
        { "weapon", characterEquipments.weapon() },
        { "offhand", characterEquipments.offhand() },
        { "amulet", characterEquipments.amulet() },
        { "ring", characterEquipments.ring() },
        { "pickaxe", characterEquipments.pickaxe() },
        { "woodaxe", characterEquipments.woodaxe() },
        { "fishingrod", characterEquipments.fishingrod() },
        { "sickle", characterEquipments.sickle() },
    };

    auto it = slotMap.find( slot );
    if ( it == slotMap.end() ) {
        std::cerr << "ItemSystem::characterEquipItem Unknown slot: " << slot << std::endl;
        return;
    }

    Model::CharacterEquipmentItem& targetSlot = it->second;

    if ( !targetSlot.id().empty() ) {
        character->inventory().addItem( targetSlot.id(), 1 );
        targetSlot.setId( "" );
        targetSlot.setItem( nullptr );
    }

    if ( !itemId.empty() ) {

        if ( !characterInventory.hasItem( itemId, 1 ) ) {
            std::cerr << "ItemSystem::characterEquipItem Item not found in inventory: " << itemId << std::endl;
            return;
        }

        const Model::CharacterInventoryItem* itemToEquip = characterInventory.itemById( itemId );

        bool canEquip = ( slot == itemToEquip->item()->category() ) ||
                        ( ( slot == "weapon" && itemToEquip->item()->type() == "weapon" ) ) ||
                        ( ( slot == "offhand" ) && itemToEquip->item()->type() == "offhand" );

        if ( !canEquip ) {
            std::cerr << "ItemSystem::characterEquipItem Item cannot be equipped in this slot: " << slot << std::endl;
            return;
        }

        targetSlot.setItem( itemToEquip->item() );
        targetSlot.setId( itemToEquip->id() );

        characterInventory.removeItem( itemId, 1 );
    }

    computeEquipmentModifiers( sessionId, character );
    QuestSystem::updateItemQuest( sessionId, character );
    NotificationSystem::notifyCharacterInventory( sessionId, character );
    NotificationSystem::notifyCharacterEquipment( sessionId, character );
}

void ItemSystem::computeEquipmentModifiers( const std::string& sessionId, Model::Character* character ) {
    auto& equipments = character->equipment();

    character->combatAttributes().clear();
    character->skills().clear();

    std::vector<Model::CharacterEquipmentItem*> characterSlot = {
        &equipments.helmet(),
        &equipments.armor(),
        &equipments.leg(),
        &equipments.boot(),
        &equipments.weapon(),
        &equipments.offhand(),
        &equipments.amulet(),
        &equipments.ring(),
        &equipments.pickaxe(),
        &equipments.woodaxe(),
        &equipments.fishingrod(),
        &equipments.sickle() };

    for ( auto* slot : characterSlot ) {
        const auto* item = slot->item();
        if ( !item ) {
            continue;
        }

        for ( const Model::ItemBonus& bonus : item->bonuses() ) {
            const std::string& type = bonus.type();
            const std::string& targetCategory = bonus.category();
            double value = bonus.value();

            if ( type == "combat" ) {
                if ( targetCategory == "attack" ) {
                    character->combatAttributes().modifyAttack( value );

                } else if ( targetCategory == "attackSpeed" ) {
                    character->combatAttributes().modifyAttackSpeed( value );

                } else if ( targetCategory == "defense" ) {
                    character->combatAttributes().modifyDefense( value );

                } else {
                    std::cerr << "ItemSystem::computeEquipmentModifiers Unknown combat attribute: " << targetCategory << std::endl;
                }

            } else if ( type == "skill" ) {

                Model::CharacterSkill* characterSkill = character->skills().skill( targetCategory );

                if ( !characterSkill ) {
                    Model::CharacterSkill newSkill;
                    newSkill.setId( targetCategory );
                    newSkill.setExperience( 0 );
                    newSkill.setLevel( 0 );
                    newSkill.setSkill( Commons::Singleton<Core::Manager::SkillManager>::instance().skill( targetCategory ) );

                    if ( !newSkill.skill() ) {
                        std::cerr << "ItemSystem::computeEquipmentModifiers Unknown skill id: " << targetCategory << std::endl;
                        return;
                    }

                    character->skills().addSkill( newSkill );
                    characterSkill = character->skills().skill( targetCategory );
                }

                if ( characterSkill ) {
                    characterSkill->modifyBonusLevel( static_cast<int>( value ) );

                } else {
                    std::cerr << "ItemSystem::computeEquipmentModifiers Unknown skill: " << targetCategory << std::endl;
                }

            } else {
                std::cerr << "ItemSystem::computeEquipmentModifiers Unknown modifier type: " << type << std::endl;
            }
        }
    }

    NotificationSystem::notifyCharacterAttributes( sessionId, character );
    NotificationSystem::notifyCharacterSkills( sessionId, character );
}

} // namespace Core::System
