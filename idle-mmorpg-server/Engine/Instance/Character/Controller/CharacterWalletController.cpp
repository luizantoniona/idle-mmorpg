#include "CharacterWalletController.h"

namespace Engine {

CharacterWalletController::CharacterWalletController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                                      Domain::CharacterWallet& wallet ) :
    CharacterController( sendMessage ),
    _wallet( wallet ) {
}

void CharacterWalletController::onEnterWorld() {
    sendMessage( MessageSenderType::CHARACTER_WALLET, _wallet.toJson() );
}

void CharacterWalletController::onTickWorld() {
}

void CharacterWalletController::onExitWorld() {
}

} // namespace Engine
