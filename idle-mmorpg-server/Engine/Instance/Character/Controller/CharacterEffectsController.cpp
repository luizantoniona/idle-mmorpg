#include "CharacterEffectsController.h"

namespace Engine {

CharacterEffectsController::CharacterEffectsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                        Domain::Character& character,
                                                        Manager::ItemManager& itemManager,
                                                        Manager::ServerConfigurationManager& configurationManager ) :
    CharacterController( eventBus, messageSender ),
    _characterEffects( character.effects() ),
    _itemManager( itemManager ),
    _configurationManager( configurationManager ),
    _tickRate( configurationManager.tickRate() ) {

    _eventBus.subscribe( CharacterEventType::EFFECT_APPLY, [ this ]( const CharacterEvent& event ) {
        onApplyEffect( event );
    } );
}

void CharacterEffectsController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_EFFECTS, _characterEffects.toJson() );
}

void CharacterEffectsController::onLeaveWorld() {
}

void CharacterEffectsController::onTick() {

    auto& effects = _characterEffects.effects();

    if ( effects.empty() ) {
        return;
    }

    std::vector<Domain::CharacterEffect> expiredEffects;
    bool effectsChanged = false;

    for ( auto& effect : effects ) {
        effect.setCounter( effect.counter() + 1 );

        if ( effect.counter() % _tickRate == 0 ) {

            if ( effect.health() > 0 ) {
                Json::Value payload;
                payload["value"] = effect.health();
                _eventBus.publish( CharacterEvent( CharacterEventType::VITAL_HEALTH_CHANGED, payload ) );
            }

            if ( effect.mana() > 0 ) {
                Json::Value payload;
                payload["value"] = effect.mana();
                _eventBus.publish( CharacterEvent( CharacterEventType::VITAL_MANA_CHANGED, payload ) );
            }

            if ( effect.stamina() > 0 ) {
                Json::Value payload;
                payload["value"] = effect.stamina();
                _eventBus.publish( CharacterEvent( CharacterEventType::VITAL_STAMINA_CHANGED, payload ) );
            }
        }

        if ( effect.counter() >= effect.duration() ) {
            expiredEffects.push_back( effect );
        }
    }

    if ( !expiredEffects.empty() ) {
        for ( const auto& effect : expiredEffects ) {
            _characterEffects.removeEffect( effect );
        }

        effectsChanged = true;
    }

    if ( effectsChanged ) {
        _messageSender.sendMessage( MessageSenderType::CHARACTER_EFFECTS, _characterEffects.toJson() );
    }
}

void CharacterEffectsController::onApplyEffect( const CharacterEvent& event ) {
    const Json::Value& payload = event.payload();
    if ( !payload.isMember( "item" ) ) {
        return;
    }

    const std::string itemId = payload[ "item" ].asString();

    const Domain::Item* itemPointer = _itemManager.itemById( itemId );
    if ( !itemPointer ) {
        return;
    }

    const Domain::ItemEffect itemEffect = itemPointer->effect();

    Domain::CharacterEffect effect;
    effect.setSource( itemId );
    effect.setSourceName( itemPointer->name() );
    effect.setHealth( itemEffect.health() );
    effect.setMana( itemEffect.mana() );
    effect.setStamina( itemEffect.stamina() );
    effect.setDuration( itemEffect.duration() );
    effect.setCounter( 0 );

    _characterEffects.addEffect( effect );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_EFFECTS, _characterEffects.toJson() );
}

} // namespace Engine
