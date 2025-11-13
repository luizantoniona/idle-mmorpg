#include "CharacterWebSocket.h"

#include <Engine/Manager/World/WorldManager.h>
#include <Infrastructure/Network/NetworkServer.h>
#include <Shared/Commons/Singleton.h>

namespace Network {

void CharacterWebSocket::handleNewMessage( const drogon::WebSocketConnectionPtr& connection, std::string&& message, const drogon::WebSocketMessageType& type ) {
    auto sessionIdPtr = connection->getContext<std::string>();

    if ( !sessionIdPtr ) {
        connection->send( R"({"error":"missing_context"})" );
        connection->shutdown();
        return;
    }

    _receiver.receive( *sessionIdPtr, message );
}

void CharacterWebSocket::handleNewConnection( const drogon::HttpRequestPtr& request, const drogon::WebSocketConnectionPtr& connection ) {
    std::cout << "[WebSocket] Nova conexão: " << connection->peerAddr().toIp() << std::endl;

    std::string sessionId;
    const auto token = request->getHeader( "Authorization" );
    const std::string prefix = "X-Session ";

    if ( !token.empty() && token.rfind( prefix, 0 ) == 0 ) {
        sessionId = token.substr( prefix.length() );

    } else {
        sessionId = request->getParameter( "sid" );
    }

    if ( sessionId.empty() ) {
        connection->send( R"({"error":"missing_session"})" );
        connection->shutdown();
        return;
    }

    const auto characterParam = request->getParameter( "character" );
    if ( characterParam.empty() ) {
        connection->send( R"({"error":"missing_character"})" );
        connection->shutdown();
        return;
    }

    int idCharacter = std::stoi( characterParam );

    auto& server = Commons::Singleton<NetworkServer>::instance();
    auto session = server.getSession( sessionId );
    if ( !session ) {
        connection->send( R"({"error":"invalid_session"})" );
        connection->shutdown();
        return;
    }

    if ( server.isSessionConnected( sessionId ) ) {
        connection->send( R"({"error":"already_connected"})" );
        connection->shutdown();
        return;
    }

    server.bindConnectionToSession( sessionId, connection );
    connection->setContext( std::make_shared<std::string>( sessionId ) );

    if ( !Commons::Singleton<Engine::WorldManager>::instance().addCharacter( sessionId, session->idUser(), idCharacter ) ) {
        connection->send( R"({"error":"invalid_character"})" );
        connection->shutdown();
        return;
    }
}

void CharacterWebSocket::handleConnectionClosed( const drogon::WebSocketConnectionPtr& connection ) {
    std::cout << "[WebSocket] Conexão encerrada: " << connection->peerAddr().toIp() << std::endl;

    auto uuidPtr = connection->getContext<std::string>();

    if ( !uuidPtr ) {
        return;
    }

    Commons::Singleton<Engine::WorldManager>::instance().removeCharacter( *uuidPtr );
    Commons::Singleton<NetworkServer>::instance().unbindConnectionFromSession( *uuidPtr );
}

} // namespace Network
