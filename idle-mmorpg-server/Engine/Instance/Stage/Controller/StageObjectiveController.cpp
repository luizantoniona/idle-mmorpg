#include "StageObjectiveController.h"

namespace Engine {

StageObjectiveController::StageObjectiveController( Domain::Stage* stage ) :
    StageController( stage ) {
}

void StageObjectiveController::onCharacterEnter( CharacterInstance* characterInstance ) {
    Domain::CharacterStage& characterStage = characterInstance->character().stage();

    characterStage.setObjectives( {} );

    for ( const auto& stageObjective : _stage->objectives() ) {
        Domain::CharacterStageObjective characterObjective;

        characterObjective.setType( stageObjective.type() );
        characterObjective.setTarget( stageObjective.target() );
        characterObjective.setStageAmount( stageObjective.amount() );
        characterObjective.setCurrentAmount( 0 );

        characterStage.addObjective( characterObjective );
    }
}

void StageObjectiveController::onCharacterExit( const std::string& sessionId ) {
}

void StageObjectiveController::onTick() {
}

void StageObjectiveController::handleMessage( CharacterInstance* characterInstance, MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
    case MessageReceiverType::CHARACTER_STAGE_NEXT:
        // TODO: Here we must give the character rewards;
        break;
    default:
        break;
    }
}

} // namespace Engine
