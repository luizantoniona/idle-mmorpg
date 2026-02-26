#include "StageActionController.h"

#include <Engine/Manager/Action/ActionManager.h>

namespace Engine {

StageActionController::StageActionController( Domain::Stage* stage,
                                              Manager::ActionManager& actionManager ) :
    StageController( stage ),
    _actionManager( actionManager ) {
}

void StageActionController::onCharacterEnter( CharacterInstance* characterInstance ) {
    auto& character = characterInstance->character();
    auto& characterActions = character.actions();

    characterActions.actions().clear();

    const int stageLevel = _stage->level();

    const auto& allActions = _actionManager.actions();

    for ( const auto& [ type, actionPtr ] : allActions ) {
        if ( !actionPtr ) {
            continue;
        }

        const auto& requirement = actionPtr->requirement();

        if ( stageLevel < requirement.stage() ) {
            continue;
        }

        Domain::CharacterAction characterAction;
        characterAction.setType( type );
        characterAction.setAction( actionPtr.get() );

        characterActions.addAction( characterAction );
    }
}

void StageActionController::onCharacterExit( const std::string& sessionId ) {
}

void StageActionController::onTick() {
}

void StageActionController::handleMessage( CharacterInstance* characterInstance, MessageReceiverType type, const Json::Value& payload ) {
    if ( type != MessageReceiverType::CHARACTER_SET_ACTION || !payload.isMember( "type" ) ) {
        return;
    }

    const Domain::ActionType actionType = static_cast<Domain::ActionType>( payload[ "type" ].asInt() );

    if ( actionType == Domain::ActionType::UNKNOWN ) {
        return;
    }

    auto& characterActions = characterInstance->character().actions();

    auto& available = characterActions.actions();
    auto it = std::find_if( available.begin(), available.end(), [ & ]( const Domain::CharacterAction& action ) {
        return action.type() == actionType;
    } );

    if ( it == available.end() ) {
        return;
    }

    const auto* definition = it->action();
    const auto& options = definition->options();

    int baseDuration = 0;
    int selectedOption = -1;

    if ( !options.empty() ) {
        if ( !payload.isMember( "option" ) ) {
            return;
        }

        int optionIndex = payload[ "option" ].asInt();

        if ( optionIndex < 0 || optionIndex >= static_cast<int>( options.size() ) ) {
            return;
        }

        const auto& option = options[ optionIndex ];

        if ( _stage->level() < option.stage() ) {
            return;
        }

        baseDuration = option.duration();
        selectedOption = optionIndex;

    } else {
        // baseDuration = definition->duration();
    }

    Domain::CharacterAction runtimeAction = *it;

    if ( selectedOption >= 0 ) {
        // runtimeAction.setSelectedOption( selectedOption );
    }

    characterActions.setCurrentAction( runtimeAction );
    characterActions.setDuration( baseDuration );
    characterActions.setCounter( 0 );
}

} // namespace Engine
