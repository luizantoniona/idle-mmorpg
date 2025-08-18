#include "LocationHelper.h"

#include <iostream>
#include <unordered_map>

namespace Commons {

bool LocationHelper::canCharacterPerformAction( Model::Character* character, const Model::LocationAction& action ) {
    const std::string& characterStructure = character->coordinates().currentStructure();
    const std::string& actionStructure = action.structure();

    if ( !actionStructure.empty() && characterStructure != actionStructure ) {
        return false;
    }

    if ( actionStructure.empty() && !characterStructure.empty() ) {
        return false;
    }

    for ( const auto& requirement : action.requirements() ) {
        const std::string& type = requirement.type();
        const std::string& id = requirement.id();

        if ( type == "skill" ) {

            Model::CharacterSkill* skill = character->skills().skill( id );
            if ( !skill || skill->level() < requirement.amount() ) {
                return false;
            }

        } else if ( type == "item" ) {
            if ( !character->inventory().hasItem( id, requirement.amount() ) ) {
                return false;
            }

        } else if ( type == "equipment" ) {
            auto& characterEquipments = character->equipment();

            std::unordered_map<std::string, Model::CharacterEquipmentItem&> slotMap = {
                { "pickaxe", characterEquipments.pickaxe() },
                { "woodaxe", characterEquipments.woodaxe() },
                { "fishrod", characterEquipments.fishrod() },
                { "shovel", characterEquipments.shovel() },
                { "sickle", characterEquipments.sickle() },
            };

            auto it = slotMap.find( id );
            if ( it == slotMap.end() ) {
                std::cerr << "EquipmentSystem::characterEquipItem Unknown slot: " << id << std::endl;
                return false;
            }

            Model::CharacterEquipmentItem& targetSlot = it->second;

            if ( targetSlot.id().empty() ) {
                return false;
            }

        } else {
            std::cerr << "LocationHelper::canCharacterPerformAction Unknown requirement type: " << type << std::endl;
            return false;
        }
    }

    return true;
}

bool LocationHelper::canCharacterUseConnections( Model::Character* character, const Model::LocationConnection& connection ) {
    const std::string& characterStructure = character->coordinates().currentStructure();
    const std::string& connectionStructure = connection.structure();

    if ( !connectionStructure.empty() && characterStructure != connectionStructure ) {
        return false;
    }

    if ( connectionStructure.empty() && !characterStructure.empty() ) {
        return false;
    }

    for ( const auto& requirement : connection.requirements() ) {
        const std::string& type = requirement.type();
        const std::string& id = requirement.id();

        if ( type == "quest" ) {
            if ( !character->quests().isQuestFinished( id ) ) {
                return false;
            }

        } else if ( type == "skill" ) {
            Model::CharacterSkill* skill = character->skills().skill( id );
            if ( !skill || skill->level() < requirement.amount() ) {
                return false;
            }

        } else if ( type == "item" ) {
            if ( !character->inventory().hasItem( id, requirement.amount() ) ) {
                return false;
            }

        } else if ( type == "equipment" ) {
            auto& characterEquipments = character->equipment();

            std::unordered_map<std::string, Model::CharacterEquipmentItem&> slotMap = {
                { "pickaxe", characterEquipments.pickaxe() },
                { "woodaxe", characterEquipments.woodaxe() },
                { "fishrod", characterEquipments.fishrod() },
                { "shovel", characterEquipments.shovel() },
                { "sickle", characterEquipments.sickle() },
            };

            auto it = slotMap.find( id );
            if ( it == slotMap.end() ) {
                std::cerr << "EquipmentSystem::canCharacterUseConnections Unknown slot: " << id << std::endl;
                return false;
            }

            Model::CharacterEquipmentItem& targetSlot = it->second;

            if ( targetSlot.id().empty() ) {
                return false;
            }

        } else {
            std::cerr << "LocationHelper::canCharacterUseConnections Unknown requirement type: " << type << std::endl;
            return false;
        }
    }

    return true;
}

bool LocationHelper::canCharacterInteractDenizen( Model::Character* character, const Model::Denizen& denizen ) {
    const std::string& characterStructure = character->coordinates().currentStructure();
    const std::string& denizenStructure = denizen.structure();

    if ( !denizenStructure.empty() && characterStructure != denizenStructure ) {
        return false;
    }

    if ( denizenStructure.empty() && !characterStructure.empty() ) {
        return false;
    }

    return true;
}

bool LocationHelper::canCharacterSeeDenizenQuest( Model::Character* character, const Model::DenizenQuest& quest ) {
    auto& quests = character->quests();
    const std::string& questId = quest.id();

    if ( quests.isQuestFinished( questId ) ) {
        return false;
    }

    if ( quests.isQuestProceeding( questId ) ) {
        if ( quests.isQuestObjectiveCompleted( questId ) ) {
            return true;
        }

        return false;
    }

    const Model::Quest* questPtr = quest.quest();
    if ( questPtr ) {
        for ( const auto& requirement : questPtr->requirements() ) {

            if ( requirement.type() == "quest" ) {
                if ( !quests.isQuestFinished( requirement.id() ) ) {
                    return false;
                }
            } else {
                std::cerr << "LocationHelper::canCharacterSeeDenizenQuest Quest requirement not mapped: " << requirement.type() << std::endl;
            }
        }
    }

    return true;
}

} // namespace Commons
