#include "CharacterActionsController.h"

namespace Engine {

CharacterActionsController::CharacterActionsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                        Domain::Character& character,
                                                        Manager::ActionManager& actionManager ) :
    CharacterController( eventBus, messageSender ),
    _character( character ),
    _characterActions( character.actions() ),
    _actionManager( actionManager ) {
}

void CharacterActionsController::onEnterWorld() {
    const auto& allActions = _actionManager.actions();

    for ( const auto& [ type, actionPtr ] : allActions ) {
        if ( !actionPtr ) {
            continue;
        }

        std::vector<Domain::CharacterActionOption> filtered;
        for ( const auto& option : actionPtr->options() ) {
            if ( _character.stage().stageLevel() >= option.stage() ) {
                Domain::CharacterActionOption charOpt;
                charOpt.setStage( option.stage() );
                charOpt.setDuration( option.duration() );
                charOpt.setExperience( option.experience() );
                charOpt.setSkill( option.skill() );
                charOpt.setItemId( option.itemId() );
                filtered.push_back( charOpt );
            }
        }

        if ( filtered.empty() ) {
            continue;
        }

        Domain::CharacterAction characterAction;
        characterAction.setType( type );
        characterAction.setDescription( actionPtr->description() );
        characterAction.setOptions( filtered );

        _characterActions.addAction( characterAction );
    }

    _messageSender.sendMessage( MessageSenderType::CHARACTER_ACTIONS, _characterActions.toJson() );
}

void CharacterActionsController::onLeaveWorld() {
}

void CharacterActionsController::onTick() {
    const Domain::CharacterAction& currentAction = _characterActions.currentAction();

    if ( currentAction.type() == Domain::ActionType::UNKNOWN || currentAction.type() == Domain::ActionType::IDLE ) {
        return;
    }

    const Domain::CharacterActionOption option = currentAction.selectedOption();
    if ( option.duration() <= 0 ) {
        return;
    }

    _characterActions.setCounter( _characterActions.counter() + 1 );

    if ( _characterActions.counter() < option.duration() ) {
        _messageSender.sendMessage( MessageSenderType::CHARACTER_ACTIONS, _characterActions.toJson() );
        return;
    }

    executeCurrentAction();

    _characterActions.setCounter( 0 );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_ACTIONS, _characterActions.toJson() );
}

void CharacterActionsController::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
    case MessageReceiverType::CHARACTER_ACTION_SET: {

        if ( !payload.isMember( "type" ) ) {
            return;
        }

        const Domain::ActionType actionType = static_cast<Domain::ActionType>( payload[ "type" ].asInt() );
        if ( actionType == Domain::ActionType::UNKNOWN ) {
            return;
        }

        auto& available = _characterActions.actions();
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

        _characterActions.setCurrentAction( runtimeAction );
        _characterActions.setDuration( selectedOption->duration() );
        _characterActions.setCounter( 0 );

        _messageSender.sendMessage( MessageSenderType::CHARACTER_ACTIONS, _characterActions.toJson() );
    }
    default:
        break;
    }
}

void CharacterActionsController::executeCurrentAction() {
    const Domain::CharacterAction& currentAction = _characterActions.currentAction();
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
    auto skills = combatSkill( &_character );
    for ( const auto& skill : skills ) {
        Json::Value payload;
        payload[ "skill" ] = static_cast<int>( skill );
        payload[ "experience" ] = option.experience();

        _eventBus.publish( CharacterEvent( CharacterEventType::SKILL_EXPERIENCE_GAINED, payload ) );
    }
}

std::vector<Domain::SkillType> CharacterActionsController::combatSkill( Domain::Character* character ) {
    const Domain::Item* weapon = character->equipment().weapon().item();
    const Domain::Item* offhand = character->equipment().offhand().item();

    std::vector<Domain::SkillType> skills = {};

    auto getSkillForWeapon = []( const Domain::Item* item ) -> Domain::SkillType {
        if ( !item ) {
            return Domain::SkillType::FIST_MASTERY;
        }

        switch ( item->category() ) {
        case Domain::ItemCategory::AXE:
            return Domain::SkillType::AXE_MASTERY;

        case Domain::ItemCategory::DAGGER:
            return Domain::SkillType::DAGGER_MASTERY;

        case Domain::ItemCategory::SWORD:
            return Domain::SkillType::SWORD_MASTERY;

        default:
            return Domain::SkillType::UNKNOWN;
        }
    };

    auto getSkillForOffhand = []( const Domain::Item* item ) -> Domain::SkillType {
        if ( !item ) {
            return Domain::SkillType::UNKNOWN;
        }

        switch ( item->category() ) {
        case Domain::ItemCategory::SHIELD:
            return Domain::SkillType::SHIELD_MASTERY;

        default:
            return Domain::SkillType::UNKNOWN;
        }
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
