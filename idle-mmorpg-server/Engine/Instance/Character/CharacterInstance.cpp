#include "CharacterInstance.h"

#include <Manager/Action/ActionManager.h>
#include <Manager/Item/ItemManager.h>
#include <Manager/Server/ServerConfigurationManager.h>
#include <Manager/Skill/SkillManager.h>
#include <Manager/Spell/SpellManager.h>
#include <Repository/Character/CharacterRepository.h>
#include <Shared/Commons/Singleton.h>

namespace Engine {

CharacterInstance::CharacterInstance( std::unique_ptr<Domain::Character> character, drogon::WebSocketConnectionPtr connection ) :
    _sessionId( "" ),
    _character( std::move( character ) ),
    _connection( connection ) {

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

    // --- Vitals ---
    _vitalsController =  std::make_unique<CharacterVitalsController>( _character->vitals() );
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
    _vitalsController->onEnterWorld();
}

void CharacterInstance::onTickWorld() {
    if ( !_character ) {
        return;
    }

    _actionsController->onTickWorld();
    _effectsController->onTickWorld();
    _equipmentController->onTickWorld();
    _inventoryController->onTickWorld();
    _skillsController->onTickWorld();
    _spellsController->onTickWorld();
    _vitalsController->onTickWorld();
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
    _vitalsController->onExitWorld();

    Repository::CharacterRepository().updateCharacter( *_character );
}

void CharacterInstance::handleMessage( const std::string& sessionId, MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
        case MessageReceiverType::UNKNOWN:
            break;
        default:
            break;
    }
}

} // namespace Engine
