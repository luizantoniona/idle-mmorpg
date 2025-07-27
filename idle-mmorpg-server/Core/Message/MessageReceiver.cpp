#include "MessageReceiver.h"

#include <Commons/Singleton.h>
#include <Core/Instance/LocationInstance.h>
#include <Core/Instance/RegionInstance.h>
#include <Core/Instance/WorldInstance.h>
#include <Core/Manager/WorldManager.h>

namespace Core::Message {

MessageReceiver::MessageReceiver() {}

void MessageReceiver::receive( const std::string& sessionId, const std::string& message ) {

    Core::Instance::WorldInstance* worldInstance = Commons::Singleton<Core::Manager::WorldManager>::instance().worldInstance();

    if ( !worldInstance ) {
        return;
    }

    Core::Instance::RegionInstance* regionInstance = worldInstance->characterRegionInstance( sessionId );

    if ( !regionInstance ) {
        return;
    }

    Core::Instance::LocationInstance* locationInstance = worldInstance->characterLocationInstance( sessionId );

    if ( !locationInstance ) {
        return;
    }

    // TODO Foward message to instance it should be fowarded
}

} // namespace Core::Message
