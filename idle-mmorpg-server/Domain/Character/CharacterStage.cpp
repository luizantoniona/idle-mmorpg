#include "CharacterStage.h"

namespace Domain {

CharacterStage::CharacterStage() :
    _stageLevel( 0 ),
    _completed( false ) {
}

Json::Value CharacterStage::toJson() const {
    Json::Value values;
    values[ "stageLevel" ] = stageLevel();
    values[ "completed" ] = completed();

    Json::Value stage;
    stage[ "stage" ] = values;
    return values;
}

int CharacterStage::stageLevel() const {
    return _stageLevel;
}

void CharacterStage::setStageLevel( int stageLevel ) {
    _stageLevel = stageLevel;
}

bool CharacterStage::completed() const {
    return _completed;
}

void CharacterStage::setCompleted( bool completed ) {
    _completed = completed;
}

} // namespace Domain
