#ifndef CHARACTERWALLETCONTROLLER_H
#define CHARACTERWALLETCONTROLLER_H

#include <Domain/Character/CharacterWallet.h>

#include "CharacterController.h"

namespace Engine {

class CharacterWalletController : public CharacterController {
public:
    explicit CharacterWalletController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage,
                                        Domain::CharacterWallet& wallet );

    void onEnterWorld() override;
    void onTickWorld() override;
    void onExitWorld() override;

private:
    Domain::CharacterWallet& _wallet;
};

} // namespace Engine

#endif // CHARACTERWALLETCONTROLLER_H
