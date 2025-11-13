#include "LocationHelper.h"

#include <iostream>
#include <unordered_map>

#include <Domain/Skill/SkillHelper.h>

namespace Helper {

bool LocationHelper::canCharacterPerformAction( Domain::Character* character, const Domain::LocationAction& action ) {
    const std::string& characterStructure = character->coordinates().structureId();
    const std::string& actionStructure = action.structure();

    if ( !actionStructure.empty() && characterStructure != actionStructure ) {
        return false;
    }

    if ( actionStructure.empty() && !characterStructure.empty() ) {
        return false;
    }

    for ( const Domain::Requirement& requirement : action.requirements() ) {
        if ( !checkRequirement( character, requirement ) ) {
            return false;
        }
    }

    return true;
}

bool LocationHelper::canCharacterUseConnections( Domain::Character* character, const Domain::LocationConnection& connection ) {
    const std::string& characterStructure = character->coordinates().structureId();
    const std::string& connectionStructure = connection.structure();

    if ( !connectionStructure.empty() && characterStructure != connectionStructure ) {
        return false;
    }

    if ( connectionStructure.empty() && !characterStructure.empty() ) {
        return false;
    }

    for ( const Domain::Requirement& requirement : connection.requirements() ) {
        if ( !checkRequirement( character, requirement ) ) {
            return false;
        }
    }

    return true;
}

bool LocationHelper::canCharacterInteractDenizen( Domain::Character* character, const Domain::Denizen& denizen ) {
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

bool LocationHelper::canCharacterSeeDenizenQuest( Domain::Character* character, const Domain::DenizenQuest& quest ) {
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

    const Domain::Quest* questPtr = quest.quest();
    if ( questPtr ) {

        for ( const Domain::Requirement& requirement : questPtr->requirements() ) {
            if ( !checkRequirement( character, requirement ) ) {
                return false;
            }
        }

        return true;
    }

    return false;
}

bool LocationHelper::checkRequirement( Domain::Character* character, const Domain::Requirement& requirement ) {
    const Domain::RequirementType type = requirement.type();

    switch ( type ) {
        case Domain::RequirementType::SKILL:
            if ( !checkSkillRequirement( character, requirement ) ) {
                return false;
            }
            break;
        case Domain::RequirementType::ITEM:
            if ( !checkItemRequirement( character, requirement ) ) {
                return false;
            }
            break;
        case Domain::RequirementType::EQUIPMENT:
            if ( !checkEquipmentRequirement( character, requirement ) ) {
                return false;
            }
            break;
        case Domain::RequirementType::QUEST:
            if ( !checkQuestRequirement( character, requirement ) ) {
                return false;
            }
            break;
        default:
            std::cerr << "LocationHelper::checkRequirement Unknown requirement type" << std::endl;
            return false;
    }

    return true;
}

bool LocationHelper::checkSkillRequirement( Domain::Character* character, const Domain::Requirement& requirement ) {
    const Domain::SkillType skillType = Helper::SkillHelper::stringToEnum( requirement.id() );

    Domain::CharacterSkill* skill = character->skills().skill( skillType );

    return skill && skill->level() >= requirement.amount();
}

bool LocationHelper::checkItemRequirement( Domain::Character* character, const Domain::Requirement& requirement ) {
    return character->inventory().hasItem( requirement.id(), requirement.amount() );
}

bool LocationHelper::checkEquipmentRequirement( Domain::Character* character, const Domain::Requirement& requirement ) {
    auto& characterEquipments = character->equipment();

    std::unordered_map<std::string, Domain::CharacterEquipmentItem&> slotMap = {
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

    Domain::CharacterEquipmentItem& targetSlot = it->second;
    return !targetSlot.id().empty();
}

bool LocationHelper::checkQuestRequirement( Domain::Character* character, const Domain::Requirement& requirement ) {
    return character->quests().isQuestFinished( requirement.id() );
}

} // namespace Helper
