#include "CharacterInstance.h"

#include <Manager/Server/ServerConfigurationManager.h>
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

    // --- Equipment ---
    /*
    auto& itemManager =
        Commons::Singleton<Manager::ItemManager>::instance();

     auto& equipment = _character->equipment();

      auto resolve = [&]( Domain::CharacterEquipmentItem& item ) {
          if ( item.id().empty() ) {
              return;
          }

         Item* resolved = itemManager.itemById( item.id() );
         if ( resolved ) {
             item.setItem( resolved );
         }
     };

      resolve( equipment.helmet() );
      resolve( equipment.armor() );
      resolve( equipment.leg() );
      resolve( equipment.boot() );
      resolve( equipment.weapon() );
      resolve( equipment.offhand() );
      resolve( equipment.amulet() );
      resolve( equipment.ring() );
      resolve( equipment.pickaxe() );
      resolve( equipment.woodaxe() );
      resolve( equipment.fishingrod() );
      resolve( equipment.sickle() );
    */

    // --- Inventory ---
    /*
    auto& itemManager =
        Commons::Singleton<Manager::ItemManager>::instance();

    auto& inventory = _character->inventory();

    for ( auto& item : inventory.items() ) {
        Item* resolved = itemManager.itemById( item.id() );
        if ( !resolved ) {
            continue;
        }

        item.setItem( resolved );
    }
    */

    // --- Skills ---
    /*
    auto& skillManager =
            Commons::Singleton<Manager::SkillManager>::instance();

         auto& skills = _character->skills();

          for ( auto& skill : skills.skills() ) {
              Skill* resolved = skillManager.skill( skill.id() );
              if ( !resolved ) {
                  continue;
              }

             skill.setSkill( resolved );
             skill.setType(
                 Domain::SkillHelper::stringToType( skill.id() )
             );
    }
    */

    // --- Spells ---
    /*
    auto& spellManager = Commons::Singleton<Manager::SpellManager>::instance();

    auto& spells = _character->spells();

    for ( auto& spell : spells.allSpells() ) {
        Spell* resolved = spellManager.spellById( spell.id() );
        if ( !resolved ) {
            continue;
        }

        spell.setSpell( resolved );
        spell.setCount( resolved->cooldown() );

        if ( resolved->type() == "healing" ) {
            spells.addHealingRuntime( &spell );
        } else if ( resolved->type() == "attack" ) {
            spells.addAttackRuntime( &spell );
        }
    }
    */

    // --- Vitals ---
    // vitals->setRegenDuration( Commons::Singleton<Manager::ServerConfigurationManager>::instance().tickRate() );

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

/*
bool CharacterInstance::addItemToInventory(
    const std::string& itemId,
    int amount
    ) {
    auto& itemManager =
        Commons::Singleton<Manager::ItemManager>::instance();

    Item* item = itemManager.itemById( itemId );
    if ( !item ) {
        return false;
    }

    auto& inventory = _character->inventory();

    inventory.addItem( itemId, amount );

    auto* inventoryItem = inventory.itemById( itemId );
    if ( inventoryItem ) {
        inventoryItem->setItem( item );
    }

    return true;
}
*/

/*
#include "CharacterEffects.h"

#include <algorithm>

namespace Domain {

CharacterEffects::CharacterEffects() {
}

Json::Value CharacterEffects::toJson() {
 Json::Value root;
 for ( auto& effect : effects() ) {
     root[ "effects" ].append( effect.toJson() );
 }
 return root;
}

std::vector<CharacterEffect>& CharacterEffects::effects() {
 return _effects;
}

void CharacterEffects::addEffect( CharacterEffect effect ) {
 for ( auto& oldEffect : _effects ) {
     if ( oldEffect.source() == effect.source() && oldEffect.type() == effect.type() && oldEffect.category() == effect.category() ) {
         oldEffect.setDuration( oldEffect.duration() + effect.duration() );
         return;
     }
 }

 _effects.push_back( effect );
}

void CharacterEffects::removeEffect( const CharacterEffect& effect ) {
 _effects.erase(
     std::remove_if( _effects.begin(), _effects.end(), [ &effect ]( const CharacterEffect& e ) {
         return e.source() == effect.source() && e.type() == effect.type() && e.category() == effect.category();
     } ),
     _effects.end() );
}

} // namespace Domain

 *
#include "CharacterEffect.h"

namespace Domain {

CharacterEffect::CharacterEffect() :
 _source( "" ),
 _sourceName( "" ),
 _type( "" ),
 _category( "" ),
 _value( 0.0 ),
 _duration( 0 ),
 _counter( 0 ) {
}

Json::Value Domain::CharacterEffect::toJson() {
 Json::Value root;
 root[ "source" ] = source();
 root[ "sourceName" ] = sourceName();
 root[ "type" ] = type();
 root[ "category" ] = category();
 root[ "value" ] = value();
 root[ "duration" ] = duration();
 root[ "counter" ] = counter();
 return root;
}

std::string CharacterEffect::source() const {
 return _source;
}

void CharacterEffect::setSource( const std::string& source ) {
 _source = source;
}

std::string CharacterEffect::sourceName() const {
 return _sourceName;
}

void CharacterEffect::setSourceName( const std::string& sourceName ) {
 _sourceName = sourceName;
}

std::string CharacterEffect::type() const {
 return _type;
}

void CharacterEffect::setType( const std::string& type ) {
 _type = type;
}

std::string CharacterEffect::category() const {
 return _category;
}

void CharacterEffect::setCategory( const std::string& category ) {
 _category = category;
}

double CharacterEffect::value() const {
 return _value;
}

void CharacterEffect::setValue( double value ) {
 _value = value;
}

int CharacterEffect::duration() const {
 return _duration;
}

void CharacterEffect::setDuration( int duration ) {
 _duration = duration;
}

int CharacterEffect::counter() const {
 return _counter;
}

void CharacterEffect::setCounter( int counter ) {
 _counter = counter;
}

} // namespace Domain

 */

/*
 * std::vector<CharacterStageObjective>& CharacterStage::objectives() {
    return _objectives;
}

const std::vector<CharacterStageObjective>& CharacterStage::objectives() const {
 return _objectives;
}

CharacterStageObjective* CharacterStage::findObjective( const std::string& objectiveId ) {
    for ( auto& objective : _objectives ) {
        if ( objective.idObjective() == objectiveId ) {
            return &objective;
        }
    }
    return nullptr;
}*/

} // namespace Engine
