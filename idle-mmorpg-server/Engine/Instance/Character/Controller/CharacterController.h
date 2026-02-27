#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include <json/json.h>

#include <Domain/Character/Character.h>
#include <Engine/Instance/Character/EventBus/CharacterEventBus.h>
#include <Engine/Instance/Character/Message/CharacterMessageSender.h>
#include <Engine/Message/MessageReceiverType.h>
#include <Engine/Message/MessageSenderType.h>

namespace Engine {

class CharacterController {
public:
    explicit CharacterController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender );
    virtual ~CharacterController();

    virtual void onEnterWorld() = 0;
    virtual void onLeaveWorld() = 0;

    virtual void onTick() = 0;

    virtual void handleMessage( MessageReceiverType type, const Json::Value& payload );

protected:
    CharacterEventBus& _eventBus;
    CharacterMessageSender& _messageSender;
};

} // namespace Engine

#endif // CHARACTERCONTROLLER_H
