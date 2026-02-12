#include "CharacterInstance.h"

#include <Manager/Action/ActionManager.h>
#include <Manager/Item/ItemManager.h>
#include <Manager/Server/ServerConfigurationManager.h>
#include <Manager/Skill/SkillManager.h>
#include <Manager/Spell/SpellManager.h>
#include <Repository/Character/CharacterRepository.h>
#include <Shared/Commons/Singleton.h>

namespace Engine {

CharacterInstance::CharacterInstance( std::unique_ptr<Domain::Character> character ) :
    _sessionId( "" ),
    _character( std::move( character ) ) {

    // --- Actions ---
    _actionsController = std::make_unique<CharacterActionsController>( _character->actions(), Commons::Singleton<Manager::ActionManager>::instance() );

    // --- Effects ---
    _effectsController = std::make_unique<CharacterEffectsController>( _character->effects() );

    // --- Equipment ---
    _equipmentController = std::make_unique<CharacterEquipmentController>( _character->equipment(), Commons::Singleton<Manager::ItemManager>::instance() );

    // --- Inventory ---
    _inventoryController = std::make_unique<CharacterInventoryController>( _character->inventory(), Commons::Singleton<Manager::ItemManager>::instance() );

    // --- Skills ---
    _skillsController = std::make_unique<CharacterSkillsController>( _character->skills(), Commons::Singleton<Manager::SkillManager>::instance() );

    // --- Spells ---
    _spellsController = std::make_unique<CharacterSpellsController>( _character->spells(), Commons::Singleton<Manager::SpellManager>::instance() );
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

    _actionsController->onEnterWorld();
    _effectsController->onEnterWorld();
    _equipmentController->onEnterWorld();
    _inventoryController->onEnterWorld();
    _skillsController->onEnterWorld();
    _spellsController->onEnterWorld();

    // --- Vitals ---
    // vitals->setRegenDuration( Commons::Singleton<Manager::ServerConfigurationManager>::instance().tickRate() );
}

void CharacterInstance::onLeaveWorld() {
    if ( !_character ) {
        return;
    }

    _actionsController->onExitWorld();
    _effectsController->onExitWorld();
    _equipmentController->onExitWorld();
    _inventoryController->onExitWorld();
    _skillsController->onExitWorld();
    _spellsController->onExitWorld();

    Repository::CharacterRepository().updateCharacter( *_character );
}

void CharacterInstance::tick() {
    if ( !_character ) {
        return;
    }
}

void CharacterInstance::handleMessage( const std::string& sessionId, MessageReceiverType type, const Json::Value& payload ) {}

} // namespace Engine
