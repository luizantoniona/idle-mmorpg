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
            std::string skillId = experienceEntry.idSkill();
            int xpGranted = experienceEntry.amount();

            if ( skillId == "combat" ) {
                auto combatSkillToTrain = combatSkill( character );
                for ( const auto& skill : combatSkillToTrain ) {
                    _progressionSystem.applyExperience( sessionId, character, skill, xpGranted );
                }

            } else {
                _progressionSystem.applyExperience( sessionId, character, skillId, xpGranted );
            }
        }

        characterAction.setCounter( 0 );

    } else {
        characterAction.setCounter( characterAction.counter() + 1 );
    }

    Core::System::NotificationSystem::notifyCurrentAction( sessionId, character );
}

std::vector<std::string> TrainingSystem::combatSkill( Model::Character* character ) {
    const Model::Item* weapon = character->equipment().weapon().item();
    const Model::Item* offhand = character->equipment().offhand().item();

    std::vector<std::string> skills = {};

    if ( !weapon && !offhand ) {
        return { "fist_mastery" };
    }

    auto getSkillForWeapon = []( const Model::Item* weapon ) -> std::string {
        if ( !weapon ) {
            return "";
        }

        const std::string& category = weapon->category();
        if ( category == "sword" ) {
            return "sword_mastery";
        }

        if ( category == "axe" ) {
            return "axe_mastery";
        }

        if ( category == "dagger" ) {
            return "dagger_mastery";
        }

        if ( category == "shield" ) {
            return "shield_mastery";
        }

        return "";
    };

    std::string leftSkill = getSkillForWeapon( weapon );
    std::string rightSkill = getSkillForWeapon( offhand );

    if ( !leftSkill.empty() ) {
        skills.push_back( leftSkill );
    }

    if ( !rightSkill.empty() && rightSkill != leftSkill ) {
        skills.push_back( rightSkill );
    }

    return skills;
}

} // namespace Core::System
