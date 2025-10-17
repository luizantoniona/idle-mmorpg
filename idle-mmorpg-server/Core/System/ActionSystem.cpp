#include "ActionSystem.h"

#include <algorithm>

#include <Commons/Singleton.h>
#include <Core/Manager/ServerConfigurationManager.h>
#include <Core/Manager/SkillManager.h>
#include <Core/System/QuestSystem.h>
#include <Helper/LocationHelper.h>
#include <Helper/SkillHelper.h>

#include "NotificationSystem.h"
#include "RegenerationSystem.h"

namespace Core::System {

ActionSystem::ActionSystem( Model::Location* location ) :
    _location( location ),
    _progressionSystem(),
    _tickRate( Commons::Singleton<Core::Manager::ServerConfigurationManager>::instance().tickRate() ) {}

void ActionSystem::changeAction( const std::string& sessionId, Model::Character* character, const Json::Value& payload ) {
    if ( !character || !payload.isObject() || !payload.isMember( "action" ) ) {
        return;
    }

    std::string actionId = payload[ "action" ].asString();
    std::string structureId = character->coordinates().structureId();

    if ( actionId == "idle" ) {
        character->action().clear();
        Core::System::NotificationSystem::notifyCurrentAction( sessionId, character );
        return;
    }

    const auto& actions = _location->actions();
    auto it = std::find_if( actions.begin(), actions.end(), [ & ]( const Model::LocationAction& action ) {
            if ( action.id() != actionId ) {
                return false;
            }

            if ( action.structure() != structureId ) {
                return false;
            }

            return true;
        } );

    if ( it == actions.end() ) {
        return;
    }

    const Model::LocationAction& selectedAction = *it;

    if ( !Helper::LocationHelper::canCharacterPerformAction( character, selectedAction ) ) {
        return;
    }

    Model::CharacterAction& action = character->action();
    action.setId( actionId );
    action.setDuration( computeActionDuration( character, selectedAction ) );
    action.setCounter( 0 );
    Core::System::NotificationSystem::notifyCurrentAction( sessionId, character );
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
                Model::SkillType skillType = Helper::SkillHelper::stringToEnum( experienceEntry.idSkill() );
                int xpGranted = experienceEntry.amount();

                _progressionSystem.applyExperience( sessionId, character, skillType, xpGranted );
            }

            if ( completedAction.type() == "gathering" ) {
                gatheringActionEffect( sessionId, character, completedAction );

            } else if ( completedAction.type() == "regenerative" ) {
                regenerativeActionEffect( sessionId, character );
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

    Model::SkillType skill;
    if ( action.id() == "mine" ) {
        skill = Model::SkillType::MINING;

    } else if ( action.id() == "woodcut" ) {
        skill = Model::SkillType::WOODCUTTING;

    } else if ( action.id() == "fish" ) {
        skill = Model::SkillType::FISHING;

    } else if ( action.id() == "gather" ) {
        skill = Model::SkillType::HERBALISM;

    } else {
        return baseDuration;
    }

    int skillLevel = character->skills().skillLevel( skill );
    double modifier = std::max( 0.5, 1.0 - 0.01 * skillLevel );
    return static_cast<int>( baseDuration * modifier );
}

void ActionSystem::regenerativeActionEffect( const std::string& sessionId, Model::Character* character ) {
    if ( !character ) {
        return;
    }

    auto& characterVitals = character->vitals();

    if ( characterVitals.health() >= characterVitals.maxHealth() && characterVitals.mana() >= characterVitals.maxMana() && characterVitals.stamina() >= characterVitals.maxStamina() ) {
        return;
    }

    RegenerationSystem::computeRegeneration( sessionId, character, 5.0 );
}

void ActionSystem::gatheringActionEffect( const std::string& sessionId, Model::Character* character, const Model::LocationAction& action ) {
    int skillLevel = 0;

    if ( action.id() == "mine" ) {
        skillLevel = character->skills().skillLevel( Model::SkillType::MINING );

    } else if ( action.id() == "woodcut" ) {
        skillLevel = character->skills().skillLevel( Model::SkillType::WOODCUTTING );

    } else if ( action.id() == "fish" ) {
        skillLevel = character->skills().skillLevel( Model::SkillType::FISHING );

    } else if ( action.id() == "gather" ) {
        skillLevel = character->skills().skillLevel( Model::SkillType::HERBALISM );
    }

    for ( const auto& loot : action.loot() ) {
        double amount = loot.realAmountByLevel( skillLevel );
        double chance = std::min( 1.0, loot.realChanceByLevel( skillLevel ) );
        if ( ( rand() / double(RAND_MAX) ) <= chance ) {
            int finalAmount = static_cast<int>( amount );
            character->inventory().addItem( loot.id(), finalAmount );
        }
    }

    QuestSystem::updateItemQuest( sessionId, character );
    NotificationSystem::notifyCharacterInventory( sessionId, character );
}

} // namespace Core::System
