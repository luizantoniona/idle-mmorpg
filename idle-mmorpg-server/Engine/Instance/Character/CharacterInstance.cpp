#include "CharacterInstance.h"

#include <Engine/Manager/Action/ActionManager.h>
#include <Engine/Manager/Item/ItemManager.h>
#include <Engine/Manager/Server/ServerConfigurationManager.h>
#include <Engine/Manager/Skill/SkillManager.h>
#include <Engine/Manager/Spell/SpellManager.h>
#include <Engine/Message/MessageHelper.h>
#include <Engine/Message/MessageSenderType.h>
#include <Infrastructure/Network/NetworkServer.h>
#include <Repository/Character/CharacterRepository.h>
#include <Shared/Commons/Singleton.h>

namespace Engine {

CharacterInstance::CharacterInstance( std::unique_ptr<Domain::Character> character, drogon::WebSocketConnectionPtr connection ) :
    _sessionId( "" ),
    _character( std::move( character ) ),
    _messageSender( connection ),
    _controllers() {

    // --- Actions ---
    _actionsController = std::make_unique<CharacterActionsController>( _eventBus, _messageSender, *_character, Commons::Singleton<Manager::ActionManager>::instance() );
    _controllers.push_back( _actionsController.get() );

    // --- Combat ---
    _combatController = std::make_unique<CharacterCombatController>( _eventBus, _messageSender, *_character, Commons::Singleton<Manager::ServerConfigurationManager>::instance() );
    _controllers.push_back( _combatController.get() );

    // --- Effects ---
    _effectsController = std::make_unique<CharacterEffectsController>( _eventBus, _messageSender, *_character );
    _controllers.push_back( _effectsController.get() );

    // --- Equipment ---
    _equipmentController = std::make_unique<CharacterEquipmentController>( _eventBus, _messageSender, *_character, Commons::Singleton<Manager::ItemManager>::instance() );
    _controllers.push_back( _equipmentController.get() );

    // --- Inventory ---
    _inventoryController = std::make_unique<CharacterInventoryController>( _eventBus, _messageSender, *_character, Commons::Singleton<Manager::ItemManager>::instance() );
    _controllers.push_back( _inventoryController.get() );

    // --- Progression ---
    _progressionController = std::make_unique<CharacterProgressionController>( _eventBus, _messageSender, *_character, Commons::Singleton<Manager::ServerConfigurationManager>::instance() );
    _controllers.push_back( _progressionController.get() );

    // --- Skills ---
    _skillsController = std::make_unique<CharacterSkillsController>( _eventBus, _messageSender, *_character, Commons::Singleton<Manager::SkillManager>::instance() );
    _controllers.push_back( _skillsController.get() );

    // --- Spells ---
    _spellsController = std::make_unique<CharacterSpellsController>( _eventBus, _messageSender, *_character, Commons::Singleton<Manager::SpellManager>::instance() );
    _controllers.push_back( _spellsController.get() );

    // --- Vitals ---
    _vitalsController = std::make_unique<CharacterVitalsController>( _eventBus, _messageSender, *_character );
    _controllers.push_back( _vitalsController.get() );

    // --- Wallet ---
    _walletControler = std::make_unique<CharacterWalletController>( _eventBus, _messageSender, *_character );
    _controllers.push_back( _walletControler.get() );
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

    _messageSender.sendMessage( MessageSenderType::CHARACTER, _character->toJson() );

    for ( auto* controller : _controllers ) {
        controller->onEnterWorld();
    }
}

void CharacterInstance::onLeaveWorld() {
    if ( !_character ) {
        return;
    }

    for ( auto* controller : _controllers ) {
        controller->onLeaveWorld();
    }

    Repository::CharacterRepository().updateCharacter( *_character );
}

void CharacterInstance::onTick() {
    if ( !_character ) {
        return;
    }

    for ( auto* controller : _controllers ) {
        controller->onTick();
    }
}

void CharacterInstance::handleMessage( MessageReceiverType type, const Json::Value& payload ) {
    switch ( type ) {
    case MessageReceiverType::CHARACTER_SET_ACTION:
        _actionsController->handleMessage( type, payload );
        break;
    default:
        break;
    }
}

void CharacterInstance::sendMessage( MessageSenderType type, const Json::Value& payload ) {
    _messageSender.sendMessage( type, payload );
}

void CharacterInstance::publishEvent( CharacterEventType type, const Json::Value& payload ) {
    _eventBus.publish( CharacterEvent( type, payload ) );
}

} // namespace Engine
