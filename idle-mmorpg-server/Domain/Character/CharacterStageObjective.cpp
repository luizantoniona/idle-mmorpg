#include "CharacterStageObjective.h"

namespace Domain {

CharacterStageObjective::CharacterStageObjective() :
    _type( "" ),
    _target( "" ),
    _stageAmount( 0 ),
    _currentAmount( 0 ) {
}

CharacterStageObjective::~CharacterStageObjective() = default;

Json::Value CharacterStageObjective::toJson() const {
    Json::Value values;
    values[ "type" ] = _type;
    values[ "target" ] = _target;
    values[ "stageAmount" ] = _stageAmount;
    values[ "currentAmount" ] = _currentAmount;
    return values;
}

std::string CharacterStageObjective::type() const {
    return _type;
}

void CharacterStageObjective::setType( const std::string& type ) {
    _type = type;
}

std::string CharacterStageObjective::target() const {
    return _target;
}

void CharacterStageObjective::setTarget( const std::string& target ) {
    _target = target;
}

int CharacterStageObjective::stageAmount() const {
    return _stageAmount;
}

void CharacterStageObjective::setStageAmount( int stageAmount ) {
    _stageAmount = stageAmount;
}

int CharacterStageObjective::currentAmount() const {
    return _currentAmount;
}

void CharacterStageObjective::setCurrentAmount( int currentAmount ) {
    _currentAmount = currentAmount;
}

} // namespace Domain
