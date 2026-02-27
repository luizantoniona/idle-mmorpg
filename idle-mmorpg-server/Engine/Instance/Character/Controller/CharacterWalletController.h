#ifndef CHARACTERWALLETCONTROLLER_H
#define CHARACTERWALLETCONTROLLER_H

#include <Domain/Character/Character.h>

#include "CharacterController.h"

namespace Engine {

class CharacterWalletController : public CharacterController {
public:
    explicit CharacterWalletController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                        Domain::Character& character );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterWallet& _characterWallet;
};

} // namespace Engine

#endif // CHARACTERWALLETCONTROLLER_H
