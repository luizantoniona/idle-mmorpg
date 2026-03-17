#include "CombatInstance.h"

#include <iostream>

#include <Engine/Manager/Server/ServerConfigurationManager.h>
#include <Shared/Commons/Singleton.h>

namespace Engine {

CombatInstance::CombatInstance( Domain::Stage* stage, const std::string& id, const std::string& name ) :
    _id( id ),
    _name( name ),
    _stage( stage ),
    _characters(),
    _creatures() {

    _combatController = std::make_unique<CombatController>( Commons::Singleton<Manager::ServerConfigurationManager>::instance() );
}

CombatInstance::~CombatInstance() = default;

std::string CombatInstance::id() const {
    return _id;
}

const std::unordered_map<std::string, CharacterInstance*>& CombatInstance::characters() const {
    return _characters;
}

bool CombatInstance::isFinished() const {
    for ( const auto& [ id, character ] : _characters ) {
        if ( character->character().vitals().health() > 0 ) {
            return false;
        }
    }
    return true;
}

Json::Value CombatInstance::instanceToJson() const {
    Json::Value root;
    root[ "id" ] = _id;
    root[ "name" ] = _name;
    root[ "characters" ] = static_cast<int>( _characters.size() );
    return root;
}

Json::Value CombatInstance::combatToJson() const {
    Json::Value values;
    Json::Value charactersJson;
    for ( const auto& [ sessionId, character ] : _characters ) {
        Json::Value characterJson = character->character().toJson();

        Json::Value combatJson = character->character().combat().toJson();
        for ( const auto& key : combatJson.getMemberNames() ) {
            characterJson[ key ] = combatJson[ key ];
        }

        Json::Value vitalsJson = character->character().vitals().toJson();
        for ( const auto& key : vitalsJson.getMemberNames() ) {
            characterJson[ key ] = vitalsJson[ key ];
        }

        charactersJson.append( characterJson );
    }
    values[ "characters" ] = charactersJson;

    Json::Value creaturesJson;
    for ( const auto& creature : _creatures ) {
        Json::Value creatureJson;
        creatureJson[ "name" ] = creature->name();
        creatureJson[ "id" ] = creature->combatId();
        creatureJson[ "icon" ] = creature->icon();
        creatureJson[ "combat" ] = creature->combat().toJson();
        creatureJson[ "vitals" ] = creature->vitals().toJson();
        creaturesJson.append( creatureJson );
    }
    values[ "creatures" ] = creaturesJson;

    return values;
}

void CombatInstance::addCharacter( const std::string& sessionId, CharacterInstance* characterInstance ) {
    _characters[ sessionId ] = characterInstance;

    Json::Value enterCombatPayload;
    characterInstance->publishEvent( CharacterEventType::COMBAT_ENTER, enterCombatPayload );
}

void CombatInstance::removeCharacter( const std::string& sessionId ) {
    auto it = _characters.find( sessionId );
    if ( it == _characters.end() ) {
        return;
    }

    Json::Value exitCombatPayload;
    it->second->publishEvent( CharacterEventType::COMBAT_EXIT, exitCombatPayload );

    _characters.erase( sessionId );
}

void CombatInstance::shutdown() {
    for ( auto& [ sessionId, characterInstance ] : _characters ) {

        Json::Value exitCombatPayload;
        characterInstance->publishEvent( CharacterEventType::COMBAT_EXIT, exitCombatPayload );
    }

    _characters.clear();
    _creatures.clear();
}

void CombatInstance::tick() {
    if ( isFinished() ) {
        return;
    }

    if ( _creatures.empty() ) {
        spawnCreatures();
    }

    processCharatersTurn();

    processCreaturesTurn();

    bool allCreaturesDead = true;
    for ( const auto& creature : _creatures ) {
        if ( creature->vitals().health() > 0 ) {
            allCreaturesDead = false;
            break;
        }
    }

    if ( allCreaturesDead ) {
        std::cout << "CombatInstance::tick All creatures dead, rewarding characters" << std::endl;

        std::vector<Domain::Creature*> creatures;

        for ( const auto& creature : _creatures ) {
            creatures.push_back( creature.get() );
        }

        _combatController->computeCharactersLoot( _characters, creatures );
        _combatController->computeCharactersExperience( _characters, creatures );

        _creatures.clear();
    }

    notifyCombat();
}

void CombatInstance::handleMessage( const std::string& sessionId, MessageReceiverType type, const Json::Value& payload ) {
}

void CombatInstance::notifyCombat() {
    Json::Value payload;

    payload[ "combat" ] = combatToJson();

    for ( const auto& [ sessionId, character ] : _characters ) {
        character->sendMessage( MessageSenderType::COMBAT, payload );
    }
}

void CombatInstance::spawnCreatures() {
    _creatures.clear();

    const auto& stageCreatures = _stage->creatures();

    for ( const auto& stageCreature : stageCreatures ) {

        for ( int i = 0; i < stageCreature.amount(); ++i ) {
            auto creatureInstance = std::make_unique<Domain::Creature>( *stageCreature.creature() );

            creatureInstance->setCombatId( _creatures.size() );

            _creatures.push_back( std::move( creatureInstance ) );
        }
    }

    std::cout << "CombatInstance::spawnCreatures [ID] " << _id << " Spawned creatures: " << _creatures.size() << std::endl;
}

void CombatInstance::processCharatersTurn() {
    for ( auto& [ sessionId, characterInstance ] : _characters ) {

        if ( characterInstance->character().vitals().health() <= 0 ) {
            continue;
        }

        Domain::Creature* target = firstAliveCreature();
        if ( !target ) {
            continue;
        }

        _combatController->resolveCharacterAttack( *characterInstance, *target );
    }
}

void CombatInstance::processCreaturesTurn() {
    for ( auto& creature : _creatures ) {

        if ( creature->vitals().health() <= 0 ) {
            continue;
        }

        CharacterInstance* target = firstAliveCharacter();
        if ( !target ) {
            continue;
        }

        _combatController->resolveCreatureAttack( *creature, *target );
    }
}

Domain::Creature* CombatInstance::firstAliveCreature() {
    for ( auto& creature : _creatures ) {
        if ( creature->vitals().health() > 0 ) {
            return creature.get();
        }
    }

    return nullptr;
}

CharacterInstance* CombatInstance::firstAliveCharacter() {
    for ( auto& [ sessionId, character ] : _characters ) {
        if ( character->character().vitals().health() > 0 ) {
            return character;
        }
    }

    return nullptr;
}

} // namespace Engine
