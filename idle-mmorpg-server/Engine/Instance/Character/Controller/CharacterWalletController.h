#ifndef CHARACTERWALLETCONTROLLER_H
#define CHARACTERWALLETCONTROLLER_H

#include <Domain/Character/CharacterWallet.h>

#include "CharacterController.h"

namespace Engine {

class CharacterWalletController : public CharacterController {
public:
    explicit CharacterWalletController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                        Domain::CharacterWallet& wallet );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterWallet& _wallet;
};

} // namespace Engine

#endif // CHARACTERWALLETCONTROLLER_H
