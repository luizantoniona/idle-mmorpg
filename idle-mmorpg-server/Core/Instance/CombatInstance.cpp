#include "CombatInstance.h"

#include <iostream>

namespace Core::Instance {

CombatInstance::CombatInstance( Model::Location* location, const std::string& id, const std::string& name, const std::string& structureId ) :
    _id( id ),
    _name( name ),
    _structureId( structureId ),
    _location( location ),
    _characters(),
    _creatures() {
}

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
        creatureJson[ "vitals" ] = creature->vitals().toJson();
        creatureJson[ "combatAction" ] = creature->combatAction().toJson();
        creaturesJson.append( creatureJson );
    }
    root[ "creatures" ] = creaturesJson;

    return root;
}

void CombatInstance::addCharacter( const std::string& sessionId, Model::Character* character ) {
    character->combatAction().setCounter( 0 );
    character->combatAction().setDuration( computeCharacterCombatActionDuration( character ) );
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
            creatureInstance->combatAction().setCounter( 0 );
            creatureInstance->combatAction().setDuration( computeCreatureCombatActionDuration( creatureInstance.get() ) );

            _creatures.push_back( std::move( creatureInstance ) );
        }
    }
}

void CombatInstance::process() {
    if ( _creatures.empty() ) {
        spawnCreatures();
        std::cout << "[Combat] Spawned creatures: " << _creatures.size() << std::endl;
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
                std::cout << "[Combat] Character " << character->name() << " attacks creature " << target->name() << std::endl;

                // TODO: calcular dano, aplicar no target
                // Exemplo fictício:
                // int damage = calculateDamage(character, target);
                // target->reduceHealth(damage);

                action.setCounter( 0 );
            }
        } else {
            action.setCounter( action.counter() + 1 );
        }
    }

    // Processar turno dos inimigos (semelhante ao dos personagens)
    for ( auto& creature : _creatures ) {
        auto& action = creature->combatAction();
        if ( creature->vitals().health() <= 0 ) {
            continue;
        }

        if ( action.counter() >= action.duration() ) {
            // Atacar personagem aleatório vivo
            Model::Character* target = nullptr;
            for ( const auto& [ sessionId, character ] : _characters ) {
                // Você pode checar se personagem está vivo, se tiver vitais
                target = character;
                break;
            }

            if ( target ) {
                std::cout << "[Combat] Creature " << creature->name() << " attacks character " << target->name() << std::endl;

                // TODO: calcular dano e aplicar no personagem
                // Exemplo fictício:
                // int damage = calculateDamage(creature.get(), target);
                // target->reduceHealth(damage);

                action.setCounter( 0 );
            }
        } else {
            action.setCounter( action.counter() + 1 );
        }
    }

    // TODO: checar se algum personagem morreu, remover da luta, notificar

    bool allCreaturesDead = true;
    for ( const auto& creature : _creatures ) {
        if ( creature->vitals().health() > 0 ) {
            allCreaturesDead = false;
            break;
        }
    }

    if ( allCreaturesDead ) {
        std::cout << "[Combat] All creatures dead, rewarding characters and respawning..." << std::endl;

        for ( const auto& [ sessionId, character ] : _characters ) {
            // Exemplo fictício: character->addExperience(100);
            std::cout << "[Combat] Rewarding character: " << character->name() << std::endl;
        }
    }
}

int CombatInstance::computeCharacterCombatActionDuration( Model::Character* character ) {
    // TODO VERIFY HOW WE WILL HANDLE THE DURATION OF AN ATACK
    // CONSIDERING:
    /*

    private:
    double _baseStrength;
    double _baseDexterity;
    double _baseConstitution;
    double _baseIntelligence;
    double _baseWisdom;

    private:
    double _baseAttack;
    double _baseAccuracy;
    double _baseDefense;
    double _baseSpeed;
    double _baseEvasion;
    double _baseCriticalChance;
    double _baseCriticalMultiplier;

     */
    return 100;
}

int CombatInstance::computeCreatureCombatActionDuration( Model::Creature* creature ) {
    // TODO VERIFY HOW WE WILL HANDLE THE DURATION OF AN ATACK
    // CONSIDERING:
    /*
     *
    double _maxAttack;
    double _minAttack;
    double _accuracy;
    double _speed;
    double _defense;
    double _evasion;
     *
     */
    return 100;
}

} // namespace Core::Instance
