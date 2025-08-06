#include "ActionSystem.h"

#include <algorithm>

#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

namespace Core::System {

ActionSystem::ActionSystem( Model::Location* location ) :
    _location( location ),
    _notificationSystem(),
    _sender(),
    _progressionSystem() {
}

void ActionSystem::notifyCharacterActions( const std::string& sessionId, Model::Character* character ) {
    Json::Value payloadLocationActions;
    Json::Value availableActions;

    for ( auto action : _location->actions() ) {
        if ( canPerformAction( character, action ) ) {
            availableActions.append( action.toJson() );
        }
    }

    payloadLocationActions[ "actions" ] = availableActions;
    _sender.send( sessionId, Message::MessageSenderType::LOCATION_UPDATE_ACTIONS, payloadLocationActions );
}

bool Core::System::ActionSystem::canPerformAction( Model::Character* character, const Model::LocationAction& action ) {
    if ( !character ) {
        return false;
    }

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
            if ( !skill || skill->level() < requirement.level() ) {
                return false;
            }

        } else if ( type == "item" ) {
            // TODO: Implementar verificação de inventário
            // if ( !character->hasItemInCategory( requirement.category() ) ) {
            return false;
            // }

        } else {
            return false;
        }
    }

    return true;
}

int ActionSystem::computeActionDuration( Model::Character* character, const Model::LocationAction& action ) {
    int baseDuration = action.duration();
    // TODO: Compute depending the action
    return baseDuration;
}

void ActionSystem::changeAction( const std::string& sessionId, Model::Character* character, const Json::Value& payload ) {
    if ( !character || !payload.isObject() || !payload.isMember( "action" ) ) {
        return;
    }

    std::string actionId = payload[ "action" ].asString();

    //TODO: Treat special actions separated -> Idle - Combat - Train

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

    if ( !canPerformAction( character, selectedAction ) ) {
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
    notifyCharacterActions( sessionId, character );
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
