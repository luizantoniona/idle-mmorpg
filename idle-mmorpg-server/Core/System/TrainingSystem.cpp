#include "TrainingSystem.h"

#include <algorithm>

#include "NotificationSystem.h"

namespace Core::System {

TrainingSystem::TrainingSystem( Model::Location* location ) :
    _location( location ),
    _progressionSystem() {}

void TrainingSystem::process( const std::string& sessionId, Model::Character* character ) {
    if ( !character ) {
        return;
    }

    Model::CharacterAction& characterAction = character->action();

    if ( characterAction.counter() >= characterAction.duration() ) {

        auto& actions = _location->actions();
        auto it = std::find_if( actions.begin(), actions.end(), [ & ]( const Model::LocationAction& action ) {
                return action.id() == characterAction.id();
            } );

        if ( it == actions.end() ) {
            return;
        }

        const Model::LocationAction& trainAction = *it;

        for ( const auto& experienceEntry : trainAction.experience() ) {
            int xpGranted = experienceEntry.amount();

            std::vector<Model::SkillType> combatSkillToTrain = combatSkill( character );
            for ( const auto& skill : combatSkillToTrain ) {
                _progressionSystem.applyExperience( sessionId, character, skill, xpGranted );
            }
        }

        characterAction.setCounter( 0 );

    } else {
        characterAction.setCounter( characterAction.counter() + 1 );
    }

    Core::System::NotificationSystem::notifyCurrentAction( sessionId, character );
}

std::vector<Model::SkillType> TrainingSystem::combatSkill( Model::Character* character ) {
    const Model::Item* weapon = character->equipment().weapon().item();
    const Model::Item* offhand = character->equipment().offhand().item();

    std::vector<Model::SkillType> skills = {};

    if ( !weapon && !offhand ) {
        return { Model::SkillType::FIST_MASTERY };
    }

    auto getSkillForWeapon = []( const Model::Item* item ) -> Model::SkillType {
        if ( !item ) {
            return Model::SkillType::FIST_MASTERY;
        }

        const std::string& category = item->category();

        if ( category == "sword" ) {
            return Model::SkillType::SWORD_MASTERY;
        }

        if ( category == "axe" ) {
            return Model::SkillType::AXE_MASTERY;
        }

        if ( category == "dagger" ) {
            return Model::SkillType::DAGGER_MASTERY;
        }

        if ( category == "shield" ) {
            return Model::SkillType::SHIELD_MASTERY;
        }

        return Model::SkillType::UNKNOWN;
    };

    Model::SkillType leftSkill = getSkillForWeapon( weapon );
    Model::SkillType rightSkill = getSkillForWeapon( offhand );

    if ( leftSkill != Model::SkillType::UNKNOWN ) {
        skills.push_back( leftSkill );
    }

    if ( rightSkill != Model::SkillType::UNKNOWN ) {
        skills.push_back( rightSkill );
    }

    return skills;
}

} // namespace Core::System
