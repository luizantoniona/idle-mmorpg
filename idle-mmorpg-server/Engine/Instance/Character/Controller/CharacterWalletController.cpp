#include "CharacterWalletController.h"

namespace Engine {

CharacterWalletController::CharacterWalletController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                                      Domain::CharacterWallet& wallet ) :
    CharacterController( eventBus, messageSender ),
    _wallet( wallet ) {
}

void CharacterWalletController::onEnterWorld() {
    _messageSender.sendMessage( MessageSenderType::CHARACTER_WALLET, _wallet.toJson() );
}

void CharacterWalletController::onLeaveWorld() {
}

void CharacterWalletController::onTick() {
}

} // namespace Engine
