#ifndef CHARACTERWEBSOCKET_H
#define CHARACTERWEBSOCKET_H

#include <drogon/WebSocketController.h>
#include <drogon/drogon.h>

#include <System/Message/MessageReceiver.h>

namespace Network {

class CharacterWebSocket : public drogon::WebSocketController<CharacterWebSocket> {
public:
    WS_PATH_LIST_BEGIN
    WS_PATH_ADD( "/ws/character" );
    WS_PATH_LIST_END

    void handleNewMessage( const drogon::WebSocketConnectionPtr& connection, std::string&& message, const drogon::WebSocketMessageType& type ) override;

    void handleNewConnection( const drogon::HttpRequestPtr& request, const drogon::WebSocketConnectionPtr& connection ) override;

    void handleConnectionClosed( const drogon::WebSocketConnectionPtr& connection ) override;

private:
    System::Message::MessageReceiver _receiver;
};

} // namespace Network

#endif // CHARACTERWEBSOCKET_H
