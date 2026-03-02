#include "CombatInstance.h"

#include <iostream>

namespace Engine {

CombatInstance::CombatInstance( Domain::Stage* stage, const std::string& id, const std::string& name ) :
    _id( id ),
    _name( name ),
    _stage( stage ),
    _characters(),
    _creatures() {

    _combatController = std::make_unique<CombatController>();
}

CombatInstance::~CombatInstance() = default;

std::string CombatInstance::id() const {
    return _id;
}

const std::unordered_map<std::string, CharacterInstance*>& CombatInstance::characters() const {
    return _characters;
}

bool CombatInstance::isFinished() const {
    return _characters.empty();
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
        characterJson[ "actions" ] = character->character().actions().toJson();
        characterJson[ "vitals" ] = character->character().vitals().toJson();
        charactersJson.append( characterJson );
    }
    values[ "characters" ] = charactersJson;

    Json::Value creaturesJson;
    for ( const auto& creature : _creatures ) {
        Json::Value creatureJson;
        creatureJson[ "name" ] = creature->name();
        creatureJson[ "id" ] = creature->combatId();
        creatureJson[ "icon" ] = creature->icon();
        creatureJson[ "actions" ] = creature->action().toJson();
        creatureJson[ "vitals" ] = creature->vitals().toJson();
        creaturesJson.append( creatureJson );
    }
    values[ "creatures" ] = creaturesJson;

    return values;
}

void CombatInstance::addCharacter( const std::string& sessionId, CharacterInstance* characterInstance ) {

    _combatController->estimateCharacterAttackSpeed( *characterInstance );
    _characters[ sessionId ] = characterInstance;
}

void CombatInstance::removeCharacter( const std::string& sessionId ) {
    _characters.erase( sessionId );
}

void CombatInstance::tick() {
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
        std::cout << "[Combat] All creatures dead, rewarding characters" << std::endl;

        std::vector<Domain::Creature*> creatures;

        for ( auto& creature : _creatures ) {
            creatures.push_back( creature.get() );
        }

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
            creatureInstance->vitals().health();

            _combatController->estimateCreatureAttackSpeed( *creatureInstance );

            _creatures.push_back( std::move( creatureInstance ) );
        }
    }

    std::cout << "CombatInstance::spawnCreatures [ID] " << _id << " Spawned creatures: " << _creatures.size() << std::endl;
}

void CombatInstance::processCharatersTurn() {
    // for ( auto& [ sessionId, character ] : _characters ) {
    //     auto& action = character->action();
    //     if ( action.counter() >= action.duration() ) {

    //         Domain::Creature* target = nullptr;
    //         for ( const auto& creature : _creatures ) {
    //             if ( creature->vitals().health() > 0 ) {
    //                 target = creature.get();
    //                 break;
    //             }
    //         }

    //         if ( target ) {
    //             // _combatSystem.computeHitDamage( sessionId, character, target );
    //             action.setCounter( 0 );
    //         }

    //     } else {

    //         if ( character->vitals().stamina() < 1 ) {
    //             continue;
    //         }

    //         action.setCounter( action.counter() + 1 );
    //     }
    // }

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
    // for ( auto& creature : _creatures ) {
    //     auto& action = creature->action();

    //     if ( creature->vitals().health() <= 0 ) {
    //         continue;
    //     }

    //     if ( action.counter() >= action.duration() ) {

    //         std::vector<std::pair<std::string, Domain::Character*> > aliveCharacters;
    //         aliveCharacters.reserve( _characters.size() );

    //         for ( const auto& [ sessionId, character ] : _characters ) {
    //             if ( character->vitals().health() > 0 ) {
    //                 aliveCharacters.emplace_back( sessionId, character );
    //             }
    //         }

    //         if ( !aliveCharacters.empty() ) {
    //             int idx = rand() % aliveCharacters.size();
    //             const auto& [ targetSessionId, target ] = aliveCharacters[ idx ];
    //             // _combatSystem.computeHitDamage( creature.get(), targetSessionId, target );
    //         }

    //         action.setCounter( 0 );

    //     } else {

    //         // if ( creature->vitals().stamina() < 1 ) {
    //         //     return;
    //         // }

    //         action.setCounter( action.counter() + 1 );
    //     }
    // }

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

// void CombatInstance::handleCharacterAttackSpell( const std::string& sessionId, Domain::Character* character, const std::string& spellId ) {
//     if ( character->vitals().health() <= 0 ) {
//         return;
//     }

//     // auto characterSpell = character->spells().attackSpell( spellId );
//     // if ( !characterSpell ) {
//     //     return;
//     // }

//     // auto spell = characterSpell->spell();
//     // if ( characterSpell->count() < spell->cooldown() ) {
//     //     return;
//     // }

//     // if ( character->vitals().mana() < spell->manaCost() ) {
//     //     return;
//     // }

//     Domain::Creature* target = nullptr;
//     for ( auto& creature : _creatures ) {
//         if ( creature->vitals().health() > 0 ) {
//             target = creature.get();
//             break;
//         }
//     }

//     if ( !target ) {
//         std::cout << "No valid target for attack spell" << std::endl;
//         return;
//     }

//     // _combatSystem.computeSpellDamage( sessionId, character, target, characterSpell );
// }

} // namespace Engine
