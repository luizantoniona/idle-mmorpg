#include "MessageSender.h"

#include <Commons/Singleton.h>
#include <Core/Message/MessageHelper.h>
#include <Network/NetworkServer.h>

namespace Core::Message {

MessageSender::MessageSender() {}

void MessageSender::send( const std::string& sessionId, const std::string& message ) {
    auto sessionOpt = Commons::Singleton<Network::NetworkServer>::instance().getSession( sessionId );

    if ( !sessionOpt || !sessionOpt->connection() ) {
        return;
    }

    sessionOpt->connection()->send( message );
}

void MessageSender::send( const std::string& sessionId, MessageSenderType type, const Json::Value& payload ) {
    Json::Value message;
    message[ "type" ] = MessageHelper::typeToString( type );
    message["payload"] = payload;

    Json::StreamWriterBuilder writer;
    const std::string serialized = Json::writeString( writer, message );

    send( sessionId, serialized );
}

} // namespace Core::Message
