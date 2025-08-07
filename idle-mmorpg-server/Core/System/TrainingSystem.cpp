#include "TrainingSystem.h"

#include <algorithm>

namespace Core::System {

TrainingSystem::TrainingSystem( Model::Location* location ) :
    _location( location ),
    _notificationSystem(),
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
                std::string combatSkillToTrain = combatSkill( character );
                _progressionSystem.applyExperience( sessionId, character, combatSkillToTrain, xpGranted );

            } else {
                _progressionSystem.applyExperience( sessionId, character, skillId, xpGranted );
            }
        }

        characterAction.setCounter( 0 );

    } else {
        characterAction.setCounter( characterAction.counter() + 1 );
    }

    _notificationSystem.notifyCurrentAction( sessionId, character );
}

std::string TrainingSystem::combatSkill( Model::Character* character ) {

    // TODO O que acontece se estiver com duas armas diferentes?
    // Quais skills upar?
    // TODO Dividir a XP entre todas?

    // if ( character->equipment().leftHand().id().empty() || character->equipment().rightHand().id().empty() ) {
    //     std::string weaponType = character->equipment();
    //     if ( weaponType == "sword" )
    //         return "swordsmanship";
    //     if ( weaponType == "bow" )
    //         return "archery";
    //     // ... outros tipos de armas
    // }

    return "unarmed";
}

} // namespace Core::System
