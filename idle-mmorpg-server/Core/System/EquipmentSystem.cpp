#include "EquipmentSystem.h"

#include <iostream>

#include "NotificationSystem.h"
#include "QuestSystem.h"

namespace Core::System {

void EquipmentSystem::computeEquipmentModifiers( const std::string& sessionId, Model::Character* character ) {
    character->attributes().resetModifiers();
    character->combatAttributes().resetModifiers();
    character->vitals().resetModifiers();

    auto& equipments = character->equipment();

    std::vector<Model::CharacterEquipmentItem*> characterSlot = {
        &equipments.helmet(),
        &equipments.armor(),
        &equipments.leg(),
        &equipments.boot(),
        &equipments.glove(),
        &equipments.leftHand(),
        &equipments.rightHand(),
        &equipments.amulet(),
        &equipments.ring(),
        &equipments.pickaxe(),
        &equipments.woodaxe(),
        &equipments.fishingrod(),
        &equipments.shovel(),
        &equipments.sickle() };

    for ( auto* slot : characterSlot ) {
        const auto* item = slot->item();
        if ( !item ) {
            continue;
        }

        for ( const Model::ItemModifier& modifier : item->modifiers() ) {
            const std::string& type = modifier.type();
            const std::string& targetId = modifier.id();
            double value = modifier.value();

            if ( type == "attribute" ) {
                if ( targetId == "strength" ) {
                    character->attributes().modifyStrength( value );

                } else if ( targetId == "dexterity" ) {
                    character->attributes().modifyDexterity( value );

                } else if ( targetId == "constitution" ) {
                    character->attributes().modifyConstitution( value );

                } else if ( targetId == "intelligence" ) {
                    character->attributes().modifyIntelligence( value );

                } else if ( targetId == "wisdom" ) {
                    character->attributes().modifyWisdom( value );

                } else {
                    std::cerr << "Unknown attribute: " << targetId << std::endl;
                }

            } else if ( type == "combat" ) {
                if ( targetId == "attack" ) {
                    character->combatAttributes().modifyAttack( value );

                } else if ( targetId == "accuracy" ) {
                    character->combatAttributes().modifyAccuracy( value );

                } else if ( targetId == "speed" ) {
                    character->combatAttributes().modifySpeed( value );

                } else if ( targetId == "defense" ) {
                    character->combatAttributes().modifyDefense( value );

                } else if ( targetId == "criticalChance" ) {
                    character->combatAttributes().modifyCriticalChance( value );

                } else if ( targetId == "criticalMultiplier" ) {
                    character->combatAttributes().modifyCriticalMultiplier( value );

                } else {
                    std::cerr << "Unknown combat attribute: " << targetId << std::endl;
                }

            } else if ( type == "vital" ) {
                if ( targetId == "health" ) {
                    character->vitals().setModifierMaxHealth( value );

                } else if ( targetId == "health_regen" ) {
                    // character->vitals().setModifierHealthRegen( value );

                } else if ( targetId == "mana" ) {
                    character->vitals().setModifierMaxMana( value );

                } else if ( targetId == "mana_regen" ) {
                    // character->vitals().setModifierManaRegen( value );

                } else if ( targetId == "stamina" ) {
                    character->vitals().setModifierMaxStamina( value );

                } else if ( targetId == "stamina_regen" ) {
                    // character->vitals().setModifierStaminaRegen( value );

                } else {
                    std::cerr << "Unknown vital: " << targetId << std::endl;
                }

            } else {
                std::cerr << "EquipmentSystem::computeEquipmentModifiers Unknown modifier type: " << type << std::endl;
            }
        }
    }

    NotificationSystem::notifyCharacterAttributes( sessionId, character );
    NotificationSystem::notifyCharacterCombatAttributes( sessionId, character );
}

void EquipmentSystem::characterEquipItem( const std::string& sessionId, Model::Character* character, const Json::Value& payload ) {
    const std::string itemId = payload[ "itemId" ].asString();
    const std::string slot = payload[ "slot" ].asString();

    auto& characterInventory = character->inventory();
    auto& characterEquipments = character->equipment();

    std::unordered_map<std::string, Model::CharacterEquipmentItem&> slotMap = {
        { "helmet", characterEquipments.helmet() },
        { "armor", characterEquipments.armor() },
        { "leg", characterEquipments.leg() },
        { "boot", characterEquipments.boot() },
        { "glove", characterEquipments.glove() },
        { "leftHand", characterEquipments.leftHand() },
        { "rightHand", characterEquipments.rightHand() },
        { "amulet", characterEquipments.amulet() },
        { "ring", characterEquipments.ring() },
        { "pickaxe", characterEquipments.pickaxe() },
        { "woodaxe", characterEquipments.woodaxe() },
        { "fishingrod", characterEquipments.fishingrod() },
        { "shovel", characterEquipments.shovel() },
        { "sickle", characterEquipments.sickle() },
    };

    auto it = slotMap.find( slot );
    if ( it == slotMap.end() ) {
        std::cerr << "EquipmentSystem::characterEquipItem Unknown slot: " << slot << std::endl;
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
            std::cerr << "EquipmentSystem::characterEquipItem Item not found in inventory: " << itemId << std::endl;
            return;
        }

        const Model::CharacterInventoryItem* itemToEquip = characterInventory.itemById( itemId );

        bool canEquip = ( slot == itemToEquip->item()->category() ) ||
                        ( ( slot == "leftHand" || slot == "rightHand" ) && itemToEquip->item()->type() == "weapon" );

        if ( !canEquip ) {
            std::cerr << "EquipmentSystem::characterEquipItem Item cannot be equipped in this slot: " << slot << std::endl;
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

} // namespace Core::System
