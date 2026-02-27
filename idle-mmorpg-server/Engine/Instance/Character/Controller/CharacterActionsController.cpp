#include "CharacterActionsController.h"

namespace Engine {

CharacterActionsController::CharacterActionsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                        Domain::CharacterActions& actions,
                                                        Manager::ActionManager& actionManager ) :
    CharacterController( eventBus, messageSender ),
    _actions( actions ),
    _actionManager( actionManager ) {
}

void CharacterActionsController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_ACTIONS, _actions.toJson() );
}

void CharacterActionsController::refreshAvailableActions( int stageLevel ) {
    _actions.actions().clear();

    const auto& allActions = _actionManager.actions();

    for ( const auto& [type, actionPtr] : allActions ) {
        if ( !actionPtr ) {
            continue;
        }

        std::vector<Domain::CharacterActionOption> filtered;
        for ( const auto& option : actionPtr->options() ) {
            if ( stageLevel >= option.stage() ) {
                Domain::CharacterActionOption charOpt;
                charOpt.setStage(option.stage());
                charOpt.setDuration(option.duration());
                charOpt.setExperience(option.experience());
                charOpt.setSkill(option.skill());
                charOpt.setItemId(option.itemId());
                filtered.push_back(charOpt);
            }
        }

        if ( filtered.empty() ) {
            continue;
        }

        Domain::CharacterAction characterAction;
        characterAction.setType( type );
        characterAction.setDescription( actionPtr->description() );
        characterAction.setOptions(filtered);

        _actions.addAction( characterAction );
    }

    _messageSender.sendMessage( MessageSenderType::CHARACTER_ACTIONS, _actions.toJson() );
}

void CharacterActionsController::handleActionMessage( const Json::Value& payload, int stageLevel ) {

    if ( !payload.isMember( "type" ) ) {
        return;
    }

    const Domain::ActionType actionType = static_cast<Domain::ActionType>( payload[ "type" ].asInt() );
    if ( actionType == Domain::ActionType::UNKNOWN ) {
        return;
    }

    auto& available = _actions.actions();
    auto it = std::find_if( available.begin(), available.end(), [ & ]( const Domain::CharacterAction& action ) {
        return action.type() == actionType;
    } );
    if ( it == available.end() ) {
        return;
    }

    const auto& options = it->options();
    if ( options.empty() ) {
        return;
    }

    if ( !payload.isMember( "optionStage" ) ) {
        return;
    }
    int optionStage = payload[ "optionStage" ].asInt();

    const Domain::CharacterActionOption* selectedOption = nullptr;
    for ( const auto& option : options ) {
        if ( option.stage() == optionStage ) {
            selectedOption = &option;
            break;
        }
    }
    if ( !selectedOption ) {
        return;
    }

    Domain::CharacterAction runtimeAction = *it;
    runtimeAction.setSelectedOption( *selectedOption );

    _actions.setCurrentAction( runtimeAction );
    _actions.setDuration( selectedOption->duration() );
    _actions.setCounter( 0 );
}

void CharacterActionsController::onLeaveWorld() {
}

void CharacterActionsController::onTick() {
    const Domain::CharacterAction& currentAction = _actions.currentAction();

    if ( currentAction.type() == Domain::ActionType::UNKNOWN || currentAction.type() == Domain::ActionType::IDLE ) {
        return;
    }

    const Domain::CharacterActionOption option = currentAction.selectedOption();
    if ( option.duration() <= 0 ) {
        return;
    }

    _actions.setCounter( _actions.counter() + 1 );

    if ( _actions.counter() < option.duration() ) {
        _messageSender.sendMessage( MessageSenderType::CHARACTER_ACTIONS, _actions.toJson() );
        return;
    }

    executeCurrentAction();

    _actions.setCounter( 0 );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_ACTIONS, _actions.toJson() );
}

void CharacterActionsController::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
    case MessageReceiverType::CHARACTER_SET_ACTION:
        _messageSender.sendMessage( MessageSenderType::CHARACTER_ACTIONS, _actions.toJson() );
    default:
        break;
    }
}

void CharacterActionsController::executeCurrentAction() {
    const Domain::CharacterAction& currentAction = _actions.currentAction();
    const auto option = currentAction.selectedOption();

    switch ( currentAction.type() ) {
    case Domain::ActionType::TRAIN:
        executeTraining( option );
        break;

    default:
        break;
    }
}

void CharacterActionsController::executeTraining( const Domain::CharacterActionOption& option ) {
    int xpGranted = option.experience();

    // auto skills = combatSkill( &_character );

    // for ( const auto& skill : skills ) {
    // Need a way to add experience and notify player. Pass CharacterSkillController?
    // _character.addExperience( skill, xpGranted );
    // }
}

// std::vector<Domain::SkillType> CharacterActionsController::combatSkill( Domain::Character* character ) {
//     const Domain::Item* weapon = character->equipment().weapon().item();
//     const Domain::Item* offhand = character->equipment().offhand().item();

//     std::vector<Domain::SkillType> skills = {};

//     auto getSkillForWeapon = []( const Domain::Item* item ) -> Domain::SkillType {
//         if ( !item ) {
//             return Domain::SkillType::FIST_MASTERY;
//         }

//         const std::string& category = item->category();

//         if ( category == "sword" ) {
//             return Domain::SkillType::SWORD_MASTERY;
//         }

//         if ( category == "axe" ) {
//             return Domain::SkillType::AXE_MASTERY;
//         }

//         if ( category == "dagger" ) {
//             return Domain::SkillType::DAGGER_MASTERY;
//         }

//         return Domain::SkillType::UNKNOWN;
//     };

//     auto getSkillForOffhand = []( const Domain::Item* item ) -> Domain::SkillType {
//         if ( !item ) {
//             return Domain::SkillType::UNKNOWN;
//         }

//         const std::string& category = item->category();

//         if ( category == "shield" ) {
//             return Domain::SkillType::SHIELD_MASTERY;
//         }

//         return Domain::SkillType::UNKNOWN;
//     };

//     Domain::SkillType weaponSkill = getSkillForWeapon( weapon );
//     Domain::SkillType offhandSkill = getSkillForOffhand( offhand );

//     if ( weaponSkill != Domain::SkillType::UNKNOWN ) {
//         skills.push_back( weaponSkill );
//     }

//     if ( offhandSkill != Domain::SkillType::UNKNOWN ) {
//         skills.push_back( offhandSkill );
//     }

//     return skills;
// }

} // namespace Engine
