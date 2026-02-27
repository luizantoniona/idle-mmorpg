#include "CharacterMessageSender.h"

#include <Engine/Message/MessageHelper.h>

namespace Engine {

CharacterMessageSender::CharacterMessageSender( drogon::WebSocketConnectionPtr connection ) :
    _connection( connection ) {
}

void CharacterMessageSender::sendMessage( MessageSenderType type, const Json::Value& payload ) const {
    if ( !_connection )
        return;

    Json::Value message;
    message[ "type" ] = MessageHelper::typeToString( type );
    message[ "payload" ] = payload;

    static Json::StreamWriterBuilder writer;
    const std::string serialized = Json::writeString( writer, message );

    _connection->send( serialized );
}

} // namespace Engine
