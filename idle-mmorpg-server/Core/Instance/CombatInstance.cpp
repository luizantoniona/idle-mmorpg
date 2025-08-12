#include "CombatInstance.h"

#include <iostream>

#include <Core/System/NotificationSystem.h>

namespace Core::Instance {

CombatInstance::CombatInstance( Model::Location* location, const std::string& id, const std::string& name, const std::string& structureId ) :
    _id( id ),
    _name( name ),
    _structureId( structureId ),
    _location( location ),
    _characters(),
    _creatures(),
    _combatSystem( location ) {}

Json::Value CombatInstance::instanceToJson() const {
    Json::Value root;
    root[ "id" ] = _id;
    root[ "name" ] = _name;
    root[ "structure" ] = _structureId;
    root[ "characters" ] = static_cast<int>( _characters.size() );
    return root;
}

Json::Value CombatInstance::combatToJson() const {
    Json::Value root;
    Json::Value charactersJson;
    for ( const auto& [sessionId, character] : _characters ) {
        Json::Value characterJson = character->toJson();
        characterJson[ "combatAction" ] = character->combatAction().toJson();
        characterJson[ "vitals" ] = character->vitals().toJson();
        charactersJson.append( characterJson );
    }
    root["characters"] = charactersJson;

    Json::Value creaturesJson;
    for ( const auto& creature : _creatures ) {
        Json::Value creatureJson;
        creatureJson[ "name" ] = creature->name();
        creatureJson[ "id" ] = creature->combatId();
        creatureJson[ "icon" ] = creature->id();
        creatureJson[ "combatAction" ] = creature->combatAction().toJson();
        creatureJson[ "vitals" ] = creature->vitals().toJson();
        creaturesJson.append( creatureJson );
    }
    root[ "creatures" ] = creaturesJson;

    return root;
}

void CombatInstance::addCharacter( const std::string& sessionId, Model::Character* character ) {
    _combatSystem.computeCombatActionDuration( character );
    _characters[sessionId] = character;
}

void CombatInstance::removeCharacter( const std::string& sessionId ) {
    _characters.erase( sessionId );
}

bool CombatInstance::isFinished() const {
    return _characters.empty();
}

std::string CombatInstance::id() const {
    return _id;
}

std::string CombatInstance::structureId() const {
    return _structureId;
}

const std::unordered_map<std::string, Model::Character*>& CombatInstance::characters() const {
    return _characters;
}

void CombatInstance::spawnCreatures() {
    _creatures.clear();

    const auto& locationCreatures = _location->creatures();

    for ( const auto& locCreature : locationCreatures ) {
        if ( locCreature.structure() != _structureId ) {
            continue;
        }

        int spawnCount = locCreature.spawnMin();
        if ( locCreature.spawnMax() > locCreature.spawnMin() ) {
            spawnCount += rand() % ( locCreature.spawnMax() - locCreature.spawnMin() + 1 );
        }

        for ( int i = 0; i < spawnCount; ++i ) {
            auto creatureInstance = std::make_unique<Model::Creature>( *locCreature.creature() );

            creatureInstance->setCombatId( _creatures.size() );
            _combatSystem.computeCombatActionDuration( creatureInstance.get() );

            _creatures.push_back( std::move( creatureInstance ) );
        }
    }

    std::cout << "CombatInstance::process [ID]" << _id << " Spawned creatures: " << _creatures.size() << std::endl;
}

void CombatInstance::process() {
    if ( _creatures.empty() ) {
        spawnCreatures();
    }

    for ( auto& [ sessionId, character ] : _characters ) {
        auto& action = character->combatAction();
        if ( action.counter() >= action.duration() ) {

            Model::Creature* target = nullptr;
            for ( const auto& creature : _creatures ) {
                if ( creature->vitals().health() > 0 ) {
                    target = creature.get();
                    break;
                }
            }

            if ( target ) {
                _combatSystem.computeHitDamage( sessionId, character, target );
                action.setCounter( 0 );
            }

        } else {
            action.setCounter( action.counter() + 1 );
        }
    }

    for ( auto& creature : _creatures ) {
        auto& action = creature->combatAction();

        if ( creature->vitals().health() <= 0 ) {
            continue;
        }

        if ( action.counter() >= action.duration() ) {

            std::vector<std::pair<std::string, Model::Character*> > aliveCharacters;
            aliveCharacters.reserve( _characters.size() );

            for ( const auto& [ sessionId, character ] : _characters ) {
                if ( character->vitals().health() > 0 ) {
                    aliveCharacters.emplace_back( sessionId, character );
                }
            }

            if ( !aliveCharacters.empty() ) {
                int idx = rand() % aliveCharacters.size();
                const auto& [ targetSessionId, target ] = aliveCharacters[ idx ];
                _combatSystem.computeHitDamage( creature.get(), targetSessionId, target );
            }

            action.setCounter( 0 );

        } else {
            action.setCounter( action.counter() + 1 );
        }
    }

    bool allCreaturesDead = true;
    for ( const auto& creature : _creatures ) {
        if ( creature->vitals().health() > 0 ) {
            allCreaturesDead = false;
            break;
        }
    }

    if ( allCreaturesDead ) {
        std::cout << "[Combat] All creatures dead, rewarding characters" << std::endl;

        std::vector<Model::Creature*> creatures;

        for ( auto& creature : _creatures ) {
            creatures.push_back( creature.get() );
        }

        _combatSystem.computeLoot( _characters, creatures );
        _combatSystem.computeExperience( _characters, creatures );

        _creatures.clear();
    }

    for ( const auto& [ sessionId, character ] : _characters ) {
        if ( character->vitals().health() <= 0 ) {
            Core::System::NotificationSystem::notifyDeadCharacter( sessionId );
        }
    }
}

} // namespace Core::Instance
