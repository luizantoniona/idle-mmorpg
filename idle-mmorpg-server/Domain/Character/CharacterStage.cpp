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

} // namespace Domain
