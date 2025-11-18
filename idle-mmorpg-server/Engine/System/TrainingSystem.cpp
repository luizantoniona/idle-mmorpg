#include "TrainingSystem.h"

#include <algorithm>

#include "NotificationSystem.h"

namespace Engine {

TrainingSystem::TrainingSystem( Domain::Location* location ) :
    _location( location ),
    _progressionSystem() {
}

void TrainingSystem::process( const std::string& sessionId, Domain::Character* character ) {
    if ( !character ) {
        return;
    }

    Domain::CharacterAction& characterAction = character->action();

    if ( characterAction.counter() >= characterAction.duration() ) {

        auto& actions = _location->actions();
        auto it = std::find_if( actions.begin(), actions.end(), [ & ]( const Domain::LocationAction& action ) {
            return action.id() == characterAction.id();
        } );

        if ( it == actions.end() ) {
            return;
        }

        const Domain::LocationAction& trainAction = *it;

        for ( const auto& experienceEntry : trainAction.experience() ) {
            int xpGranted = experienceEntry.amount();

            std::vector<Domain::SkillType> combatSkillToTrain = combatSkill( character );
            for ( const auto& skill : combatSkillToTrain ) {
                _progressionSystem.applyExperience( sessionId, character, skill, xpGranted );
            }
        }

        characterAction.setCounter( 0 );

    } else {
        characterAction.setCounter( characterAction.counter() + 1 );
    }

    Engine::NotificationSystem::notifyCurrentAction( sessionId, character );
}

std::vector<Domain::SkillType> TrainingSystem::combatSkill( Domain::Character* character ) {
    const Domain::Item* weapon = character->equipment().weapon().item();
    const Domain::Item* offhand = character->equipment().offhand().item();

    std::vector<Domain::SkillType> skills = {};

    auto getSkillForWeapon = []( const Domain::Item* item ) -> Domain::SkillType {
        if ( !item ) {
            return Domain::SkillType::FIST_MASTERY;
        }

        const std::string& category = item->category();

        if ( category == "sword" ) {
            return Domain::SkillType::SWORD_MASTERY;
        }

        if ( category == "axe" ) {
            return Domain::SkillType::AXE_MASTERY;
        }

        if ( category == "dagger" ) {
            return Domain::SkillType::DAGGER_MASTERY;
        }

        return Domain::SkillType::UNKNOWN;
    };

    auto getSkillForOffhand = []( const Domain::Item* item ) -> Domain::SkillType {
        if ( !item ) {
            return Domain::SkillType::UNKNOWN;
        }

        const std::string& category = item->category();

        if ( category == "shield" ) {
            return Domain::SkillType::SHIELD_MASTERY;
        }

        return Domain::SkillType::UNKNOWN;
    };

    Domain::SkillType weaponSkill = getSkillForWeapon( weapon );
    Domain::SkillType offhandSkill = getSkillForOffhand( offhand );

    if ( weaponSkill != Domain::SkillType::UNKNOWN ) {
        skills.push_back( weaponSkill );
    }

    if ( offhandSkill != Domain::SkillType::UNKNOWN ) {
        skills.push_back( offhandSkill );
    }

    return skills;
}

} // namespace Engine
