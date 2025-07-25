#include "MessageReceiver.h"

#include <Commons/Singleton.h>
#include <System/Instance/LocationInstance.h>
#include <System/Instance/RegionInstance.h>
#include <System/Instance/WorldInstance.h>
#include <System/Manager/WorldManager.h>

namespace System::Message {

MessageReceiver::MessageReceiver() {}

void MessageReceiver::receive( const std::string& sessionId, const std::string& message ) {

    System::Instance::WorldInstance* worldInstance = Commons::Singleton<System::Manager::WorldManager>::instance().worldInstance();

    if ( !worldInstance ) {
        return;
    }

    System::Instance::RegionInstance* regionInstance = worldInstance->characterRegionInstance( sessionId );

    if ( !regionInstance ) {
        return;
    }

    System::Instance::LocationInstance* locationInstance = worldInstance->characterLocationInstance( sessionId );

    if ( !locationInstance ) {
        return;
    }

    // TODO Foward message to instance it should be fowarded
}

} // namespace System::Message
