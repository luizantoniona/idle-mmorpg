#ifndef SERVERCONFIGURATIONMANAGER_H
#define SERVERCONFIGURATIONMANAGER_H

#include <string>

namespace Manager {

class ServerConfigurationManager {
public:
    ServerConfigurationManager();

    void initialize( const std::string& configurationPath );

    int tickRate() const;
    void setTickRate( int tickRate );

    int threadPool() const;
    void setThreadPool( int threadPool );

private:
    int _tickRate;
    int _threadPool;
};

} // namespace Manager

#endif // SERVERCONFIGURATIONMANAGER_H
