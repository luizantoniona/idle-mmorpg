#include "EffectSystem.h"

#include <iostream>

#include <Commons/Singleton.h>
#include <Core/Manager/ServerConfigurationManager.h>

#include "NotificationSystem.h"

namespace Core::System {

void EffectSystem::processEffects( const std::string& sessionId, Domain::Character* character ) {
    auto& effects = character->effects().effects();

    if ( effects.empty() ) {
        return;
    }

    auto& vitals = character->vitals();

    const int tickRate = Commons::Singleton<Engine::ServerConfigurationManager>::instance().tickRate();
    bool vitalsChanged = false;
    std::vector<Domain::CharacterEffect> expiredEffects = {};

    for ( auto& effect : effects ) {

        effect.setCounter( effect.counter() + 1 );

        if ( effect.counter() % tickRate == 0 ) {
            if ( effect.type() == "vital" ) {

                if ( effect.category() == "health" ) {
                    double newHealth = std::min( vitals.health() + effect.value(), vitals.maxHealth() );
                    if ( newHealth != vitals.health() ) {
                        vitals.setHealth( newHealth );
                        vitalsChanged = true;
                    }

                } else if ( effect.category() == "stamina" ) {
                    double newStamina = std::min( vitals.stamina() + effect.value(), vitals.maxStamina() );
                    if ( newStamina != vitals.stamina() ) {
                        vitals.setStamina( newStamina );
                        vitalsChanged = true;
                    }

                } else if ( effect.category() == "mana" ) {
                    double newMana = std::min( vitals.mana() + effect.value(), vitals.maxMana() );
                    if ( newMana != vitals.mana() ) {
                        vitals.setMana( newMana );
                        vitalsChanged = true;
                    }

                } else {
                    std::cerr << "EffectSystem::computeEffects Unknown vital category: " << effect.category() << std::endl;
                }

            } else {
                std::cerr << "EffectSystem::computeEffects Unknown type: " << effect.type() << std::endl;
            }
        }

        if ( effect.counter() >= effect.duration() ) {
            expiredEffects.push_back( effect );
        }
    }

    for ( const auto& effect : expiredEffects ) {
        character->effects().removeEffect( effect );
    }

    if ( vitalsChanged ) {
        NotificationSystem::notifyCharacterVitals( sessionId, character );
    }

    NotificationSystem::notifyCharacterEffects( sessionId, character );
}

} // namespace Core::System
