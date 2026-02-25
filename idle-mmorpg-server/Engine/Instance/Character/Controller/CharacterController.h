#ifndef CHARACTERCONTROLLER_H
#define CHARACTERCONTROLLER_H

#include <functional>

#include <json/json.h>

#include <Engine/Message/MessageReceiverType.h>
#include <Engine/Message/MessageSenderType.h>

namespace Engine {

class CharacterController {
public:
    CharacterController( std::function<void( MessageSenderType, const Json::Value& )> sendMessage );

    virtual ~CharacterController();

    virtual void onEnterWorld() = 0;
    virtual void onLeaveWorld() = 0;

    virtual void onTick() = 0;

    virtual void handleMessage( MessageReceiverType type, const Json::Value& payload );

protected:
    void sendMessage( MessageSenderType type, const Json::Value& payload );

private:
    std::function<void( MessageSenderType, const Json::Value& )> _sendMessage;
};

} // namespace Engine

#endif // CHARACTERCONTROLLER_H
