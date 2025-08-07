#include "ActionSystem.h"

#include <algorithm>

#include <Commons/ActionsHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

namespace Core::System {

ActionSystem::ActionSystem( Model::Location* location ) :
    _location( location ),
    _notificationSystem(),
    _sender(),
    _progressionSystem() {
}

int ActionSystem::computeActionDuration( Model::Character* character, const Model::LocationAction& action ) {
    int baseDuration = action.duration();
    // TODO: Compute depending the action
    // TODO: Treat special actions separated -> Combat - Train
    return baseDuration;
}

void ActionSystem::changeAction( const std::string& sessionId, Model::Character* character, const Json::Value& payload ) {
    if ( !character || !payload.isObject() || !payload.isMember( "action" ) ) {
        return;
    }

    std::string actionId = payload[ "action" ].asString();

    if ( actionId == "idle" ) {
        character->action().clear();
        _notificationSystem.notifyCurrentAction( sessionId, character );
        return;
    }

    const auto& actions = _location->actions();
    auto it = std::find_if( actions.begin(), actions.end(), [ & ]( const Model::LocationAction& action ) {
            return action.id() == actionId;
        } );

    if ( it == actions.end() ) {
        return;
    }

    const Model::LocationAction& selectedAction = *it;

    if ( !Commons::ActionsHelper::canCharacterPerformAction( character, selectedAction ) ) {
        return;
    }

    Model::CharacterAction& action = character->action();
    action.setId( actionId );
    action.setDuration( computeActionDuration( character, selectedAction ) );
    action.setCounter( 0 );
}

void ActionSystem::changeStructure( const std::string& sessionId, Model::Character* character, const Json::Value& payload ) {
    if ( !character || !payload.isObject() || !payload.isMember( "structure" ) ) {
        return;
    }

    std::string structureId = payload[ "structure" ].asString();

    if ( character->coordinates().currentStructure() == structureId ) {
        return;
    }

    character->coordinates().setCurrentStructure( structureId );
    character->action().clear();

    _notificationSystem.notifyCurrentAction( sessionId, character );
    _notificationSystem.notifyCurrentCoordinates( sessionId, character );
    _notificationSystem.notifyLocationActions( sessionId, character, _location );
}

void ActionSystem::process( const std::string& sessionId, Model::Character* character ) {
    if ( !character ) {
        return;
    }

    Model::CharacterAction& characterAction = character->action();

    if ( characterAction.counter() >= characterAction.duration() ) {

        const auto& actions = _location->actions();
        auto it = std::find_if( actions.begin(), actions.end(), [ & ]( const Model::LocationAction& action ) {
            return action.id() == characterAction.id();
        } );

        if ( it != actions.end() ) {
            const Model::LocationAction& completedAction = *it;

            for ( const auto& experienceEntry : completedAction.experience() ) {
                std::string skillId = experienceEntry.idSkill();
                int xpGranted = experienceEntry.amount();

                _progressionSystem.applyExperience( sessionId, character, skillId, xpGranted );
            }
        }

        characterAction.setCounter( 0 );

    } else {
        characterAction.setCounter( characterAction.counter() + 1 );
    }

    _notificationSystem.notifyCurrentAction( sessionId, character );
}

} // namespace Core::System
