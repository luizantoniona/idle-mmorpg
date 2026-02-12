#include "MessageReceiver.h"

#include <Manager/World/WorldManager.h>
#include <Shared/Commons/Singleton.h>
#include <Shared/Helper/JsonHelper.h>

namespace Engine {

MessageReceiver::MessageReceiver() {
    _worldManager = &Commons::Singleton<Manager::WorldManager>::instance();
}

void MessageReceiver::receive( const std::string& sessionId, const std::string& message ) {
    if ( message.empty() ) {
        return;
    }

    Json::Value messageJson = Helper::JsonHelper::parseJsonString( message );
    if ( messageJson.isNull() || !messageJson.isObject() ) {
        return;
    }

    _worldManager->handleMessage( sessionId, messageJson );
}

} // namespace Engine
