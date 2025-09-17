#include "LocationHelper.h"

#include <iostream>
#include <unordered_map>

namespace Helper {

bool LocationHelper::canCharacterPerformAction( Model::Character* character, const Model::LocationAction& action ) {
    const std::string& characterStructure = character->coordinates().structureId();
    const std::string& actionStructure = action.structure();

    if ( !actionStructure.empty() && characterStructure != actionStructure ) {
        return false;
    }

    if ( actionStructure.empty() && !characterStructure.empty() ) {
        return false;
    }

    for ( const Model::Requirement& requirement : action.requirements() ) {
        const Model::RequirementType type = requirement.type();
        const std::string& id = requirement.id();

        // New way

        switch ( requirement.type() ) {
        case Model::RequirementType::SKILL:
            if ( !checkSkillRequirement( character, requirement ) ) {
                return false;
            }
            break;
        case Model::RequirementType::ITEM:
            if ( !checkItemRequirement( character, requirement ) ) {
                return false;
            }
            break;
        case Model::RequirementType::EQUIPMENT:
            if ( !checkEquipmentRequirement( character, requirement ) ) {
                return false;
            }
            break;
        case Model::RequirementType::QUEST:
            if ( !checkQuestRequirement( character, requirement ) ) {
                return false;
            }
            break;
        default:
            std::cerr << "LocationHelper::canCharacterPerformAction Unknown requirement type" << std::endl;
            return false;
        }
    }

    return true;
}

bool LocationHelper::canCharacterUseConnections( Model::Character* character, const Model::LocationConnection& connection ) {
    const std::string& characterStructure = character->coordinates().structureId();
    const std::string& connectionStructure = connection.structure();

    if ( !connectionStructure.empty() && characterStructure != connectionStructure ) {
        return false;
    }

    if ( connectionStructure.empty() && !characterStructure.empty() ) {
        return false;
    }

    for ( const Model::Requirement& requirement : connection.requirements() ) {
        const Model::RequirementType type = requirement.type();
        const std::string& id = requirement.id();

        // New way

        switch ( requirement.type() ) {
        case Model::RequirementType::SKILL:
            if ( !checkSkillRequirement( character, requirement ) ) {
                return false;
            }
            break;
        case Model::RequirementType::ITEM:
            if ( !checkItemRequirement( character, requirement ) ) {
                return false;
            }
            break;
        case Model::RequirementType::EQUIPMENT:
            if ( !checkEquipmentRequirement( character, requirement ) ) {
                return false;
            }
            break;
        case Model::RequirementType::QUEST:
            if ( !checkQuestRequirement( character, requirement ) ) {
                return false;
            }
            break;
        default:
            std::cerr << "LocationHelper::canCharacterUseConnections Unknown requirement type" << std::endl;
            return false;
        }
    }

    return true;
}

bool LocationHelper::canCharacterInteractDenizen( Model::Character* character, const Model::Denizen& denizen ) {
    const std::string& characterStructure = character->coordinates().structureId();
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

        for ( const Model::Requirement& requirement : questPtr->requirements() ) {
            const Model::RequirementType type = requirement.type();
            const std::string& id = requirement.id();

            // New way

            switch ( requirement.type() ) {
            case Model::RequirementType::SKILL:
                if ( !checkSkillRequirement( character, requirement ) ) {
                    return false;
                }
                break;
            case Model::RequirementType::ITEM:
                if ( !checkItemRequirement( character, requirement ) ) {
                    return false;
                }
                break;
            case Model::RequirementType::EQUIPMENT:
                if ( !checkEquipmentRequirement( character, requirement ) ) {
                    return false;
                }
                break;
            case Model::RequirementType::QUEST:
                if ( !checkQuestRequirement( character, requirement ) ) {
                    return false;
                }
                break;
            default:
                std::cerr << "LocationHelper::canCharacterUseConnections Unknown requirement type" << std::endl;
                return false;
            }
        }

        return true;
    }

    return false;
}

bool LocationHelper::checkSkillRequirement( Model::Character* character, const Model::Requirement& requirement ) {
    Model::CharacterSkill* skill = character->skills().skill( requirement.id() );
    return skill && skill->level() >= requirement.amount();
}

bool LocationHelper::checkItemRequirement( Model::Character* character, const Model::Requirement& requirement ) {
    return character->inventory().hasItem( requirement.id(), requirement.amount() );
}

bool LocationHelper::checkEquipmentRequirement( Model::Character* character, const Model::Requirement& requirement ) {
    auto& characterEquipments = character->equipment();

    std::unordered_map<std::string, Model::CharacterEquipmentItem&> slotMap = {
        { "pickaxe", characterEquipments.pickaxe() },
        { "woodaxe", characterEquipments.woodaxe() },
        { "fishingrod", characterEquipments.fishingrod() },
        { "sickle", characterEquipments.sickle() },
    };

    auto it = slotMap.find( requirement.id() );
    if ( it == slotMap.end() ) {
        std::cerr << "LocationHelper::checkEquipmentRequirement Unknown slot: " << requirement.id() << std::endl;
        return false;
    }

    Model::CharacterEquipmentItem& targetSlot = it->second;
    return !targetSlot.id().empty();
}

bool LocationHelper::checkQuestRequirement( Model::Character* character, const Model::Requirement& requirement ) {
    return character->quests().isQuestFinished( requirement.id() );
}

} // namespace Helper
