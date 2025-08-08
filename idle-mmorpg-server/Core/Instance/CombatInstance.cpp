#include "CombatInstance.h"

#include <iostream>

namespace Core::Instance {

CombatInstance::CombatInstance( Model::Location* location, const int id, const std::string& structureId ) :
    _id( id ),
    _structureId( structureId ),
    _location( location ) {}

Json::Value CombatInstance::toJson() const {
    Json::Value root;
    root["id"] = _id;
    root["structure"] = _structureId;
    root["characters"] = static_cast<int>( _characters.size() );
    return root;
}

void CombatInstance::addCharacter( const std::string& sessionId, Model::Character* character ) {
    _characters[sessionId] = character;
}

void CombatInstance::removeCharacter( const std::string& sessionId ) {
    _characters.erase( sessionId );
}

bool CombatInstance::isFinished() const {
    return _characters.empty();
}

int CombatInstance::id() const {
    return _id;
}

std::string CombatInstance::structureId() const {
    return _structureId;
}

const std::unordered_map<std::string, Model::Character*>& CombatInstance::characters() const {
    return _characters;
}

void CombatInstance::process() {
    for ( const auto& [sessionId, character] : _characters ) {
        std::cout << "[Combat] Processing character: " << character->name() << std::endl;
    }
}

}
