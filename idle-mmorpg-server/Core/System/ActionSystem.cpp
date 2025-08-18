#include "ActionSystem.h"

#include <algorithm>

#include <Commons/LocationHelper.h>
#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>

#include "NotificationSystem.h"

namespace Core::System {

ActionSystem::ActionSystem( Model::Location* location ) :
    _location( location ),
    _progressionSystem() {
}

void ActionSystem::changeAction( const std::string& sessionId, Model::Character* character, const Json::Value& payload ) {
    if ( !character || !payload.isObject() || !payload.isMember( "action" ) ) {
        return;
    }

    std::string actionId = payload[ "action" ].asString();

    if ( actionId == "idle" ) {
        character->action().clear();
        Core::System::NotificationSystem::notifyCurrentAction( sessionId, character );
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

    if ( !Commons::LocationHelper::canCharacterPerformAction( character, selectedAction ) ) {
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

    Core::System::NotificationSystem::notifyCurrentAction( sessionId, character );
    Core::System::NotificationSystem::notifyCurrentCoordinates( sessionId, character );
    Core::System::NotificationSystem::notifyLocationActions( sessionId, character, _location );
    Core::System::NotificationSystem::notifyLocationDenizens( sessionId, character, _location );
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

            if ( completedAction.id() == "rest" || completedAction.id() == "sleep" ) {
                regenerativeActionEffect( character );
                NotificationSystem::notifyCharacterVitals( sessionId, character );
            }
        }

        characterAction.setCounter( 0 );

    } else {
        characterAction.setCounter( characterAction.counter() + 1 );
    }

    Core::System::NotificationSystem::notifyCurrentAction( sessionId, character );
}

int ActionSystem::computeActionDuration( Model::Character* character, const Model::LocationAction& action ) {
    int baseDuration = action.duration();
    // TODO: Compute depending the action
    // TODO: Treat special actions separated -> Combat - Train
    return baseDuration;
}

void ActionSystem::regenerativeActionEffect( Model::Character* character ) {
    if ( !character ) {
        return;
    }

    const double healthRegen = 5 + character->vitals().baseHealthRegen() + character->attributes().constitution();
    const double staminaRegen = 2 + character->vitals().baseStaminaRegen() + character->attributes().constitution();
    const double manaRegen = 1 + character->vitals().baseManaRegen() + +character->attributes().constitution();

    int newHealth = character->vitals().health() + healthRegen;
    if ( newHealth > character->vitals().fullHealth() ) {
        newHealth = character->vitals().fullHealth();
    }
    character->vitals().setHealth( newHealth );

    int newStamina = character->vitals().stamina() + staminaRegen;
    if ( newStamina > character->vitals().fullStamina() ) {
        newStamina = character->vitals().fullStamina();
    }
    character->vitals().setStamina( newStamina );

    int newMana = character->vitals().mana() + manaRegen;
    if ( newMana > character->vitals().fullMana() ) {
        newMana = character->vitals().fullMana();
    }
    character->vitals().setMana( newMana );
}

} // namespace Core::System
