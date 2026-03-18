#include "CharacterStage.h"

namespace Domain {

CharacterStage::CharacterStage() :
    _stageLevel( 0 ),
    _completed( false ),
    _objectives() {
}

Json::Value CharacterStage::toJson() const {
    Json::Value values;
    values[ "stageLevel" ] = _stageLevel;
    values[ "completed" ] = _completed;

    for ( auto& objective : _objectives ) {
        values[ "objectives" ].append( objective.toJson() );
    }

    Json::Value stage;
    stage[ "stage" ] = values;
    return stage;
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

std::vector<CharacterStageObjective> CharacterStage::objectives() const {
    return _objectives;
}

void CharacterStage::setObjectives( const std::vector<CharacterStageObjective>& objectives ) {
    _objectives = objectives;
}

void CharacterStage::addObjective( const CharacterStageObjective& objective ) {
    _objectives.push_back( objective );
}

} // namespace Domain
