#include "CharacterInstance.h"

#include <Repository/Character/CharacterRepository.h>

namespace Engine {

CharacterInstance::CharacterInstance( std::unique_ptr<Domain::Character> character ) :
    _sessionId( "" ),
    _character( std::move( character ) ) {
}

std::string CharacterInstance::sessionId() const {
    return _sessionId;
}

void CharacterInstance::setSessionId( const std::string& sessionId ) {
    _sessionId = sessionId;
}

Domain::Character& CharacterInstance::character() {
    return *_character;
}

void CharacterInstance::onEnterWorld() {
    if ( !_character ) {
        return;
    }

    // Aqui entra SOMENTE lógica de runtime
    // Nada de banco, nada de repository

    // Exemplos futuros:
    // - Resolver ponteiros de itens (ItemManager)
    // - Resolver spells / skills
    // - Inicializar cooldowns
    // - Resetar estados transitórios

    // Exemplo conceitual:
    // _character->equipment().resolveRuntimePointers();
}

void CharacterInstance::onLeaveWorld() {
    if ( !_character ) {
        return;
    }

    // Antes de salvar, "limpa" qualquer coisa de runtime
    // Exemplo:
    // _character->equipment().clearRuntimePointers();

    Repository::CharacterRepository().updateCharacter( *_character );
}

void CharacterInstance::tick() {
    if ( !_character ) {
        return;
    }

    // NÃO salvar aqui por enquanto
    // Esse tick é puramente gameplay

    // Exemplo futuro:
    // _character->vitals().tick();
    // _character->buffs().tick();
}

} // namespace Engine
