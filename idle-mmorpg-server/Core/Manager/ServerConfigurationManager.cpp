#include "ServerConfigurationManager.h"

namespace Core::Manager {

ServerConfigurationManager::ServerConfigurationManager() :
    _tickRate( 20 ),
    _threadPool( 4 ) {
}

int ServerConfigurationManager::tickRate() const {
    return _tickRate;
}

void ServerConfigurationManager::setTickRate( int tickRate ) {
    _tickRate = tickRate;
}

} // namespace Core::Manager
