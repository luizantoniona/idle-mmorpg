#include "CharacterEffectsController.h"

namespace Engine {

CharacterEffectsController::CharacterEffectsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                        Domain::Character& character ) :
    CharacterController( eventBus, messageSender ),
    _characterEffects( character.effects() ) {

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
}

void CharacterEffectsController::onApplyEffect( const CharacterEvent& event ) {
    Json::Value payload = event.payload();

    Domain::CharacterEffect effect;
    effect.setSource( payload[ "effect" ][ "source" ].asString() );
    effect.setSourceName( payload[ "effect" ][ "sourceName" ].asString() );
    effect.setType( payload[ "effect" ][ "type" ].asString() );
    effect.setCategory( payload[ "effect" ][ "category" ].asString() );
    effect.setValue( payload[ "effect" ][ "value" ].asDouble() );
    effect.setDuration( payload[ "effect" ][ "duration" ].asInt() );
    effect.setCounter( payload[ "effect" ][ "counter" ].asInt() );

    _characterEffects.addEffect( effect );

    _messageSender.sendMessage( MessageSenderType::CHARACTER_EFFECTS, _characterEffects.toJson() );
}

} // namespace Engine
