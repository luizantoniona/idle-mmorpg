#include "CharacterStage.h"

namespace Domain {

CharacterStage::CharacterStage() :
    _idStage( "" ),
    _completed( false ) {
}

std::string CharacterStage::idStage() const {
    return _idStage;
}

void CharacterStage::setIdStage( const std::string& idStage ) {
    _idStage = idStage;
}

bool CharacterStage::completed() const {
    return _completed;
}

void CharacterStage::setCompleted( bool completed ) {
    _completed = completed;
}

std::vector<CharacterStageObjective>& CharacterStage::objectives() {
    return _objectives;
}

const std::vector<CharacterStageObjective>& CharacterStage::objectives() const {
    return _objectives;
}

CharacterStageObjective* CharacterStage::findObjective( const std::string& objectiveId ) {
    for ( auto& objective : _objectives ) {
        if ( objective.idObjective() == objectiveId ) {
            return &objective;
        }
    }
    return nullptr;
}

} // namespace Domain
