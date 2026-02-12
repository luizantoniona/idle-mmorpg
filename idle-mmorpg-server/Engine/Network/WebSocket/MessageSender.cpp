#include "MessageSender.h"

#include <Engine/Message/MessageHelper.h>
#include <Infrastructure/Network/NetworkServer.h>
#include <Shared/Commons/Singleton.h>

namespace Engine {

void MessageSender::send( const std::string& sessionId, MessageSenderType type, const Json::Value& payload ) {
    Json::Value message;
    message[ "type" ] = MessageHelper::typeToString( type );
    message[ "payload" ] = payload;

    Json::StreamWriterBuilder writer;
    const std::string serialized = Json::writeString( writer, message );

    send( sessionId, serialized );
}

void MessageSender::send( const std::string& sessionId, const std::string& message ) {
    auto sessionOpt = Commons::Singleton<Network::NetworkServer>::instance().getSession( sessionId );

    if ( !sessionOpt || !sessionOpt->connection() ) {
        return;
    }

    sessionOpt->connection()->send( message );
}

} // namespace Engine
