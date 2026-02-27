#include "CharacterWalletController.h"

namespace Engine {

CharacterWalletController::CharacterWalletController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::Character& character ) :
    CharacterController( eventBus, messageSender ),
    _characterWallet( character.wallet() ) {
}

void CharacterWalletController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_WALLET, _characterWallet.toJson() );
}

void CharacterWalletController::onLeaveWorld() {
}

void CharacterWalletController::onTick() {
}

} // namespace Engine
