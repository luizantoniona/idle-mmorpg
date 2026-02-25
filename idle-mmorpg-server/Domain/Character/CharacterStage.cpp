#include "CharacterStage.h"

namespace Domain {

CharacterStage::CharacterStage() :
    _idStage( "" ),
    _completed( false ) {
}

Json::Value CharacterStage::toJson() const {
    Json::Value values;
    values[ "idStage" ] = idStage();
    values[ "completed" ] = completed();

    Json::Value stage;
    stage[ "stage" ] = values;
    return values;
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
