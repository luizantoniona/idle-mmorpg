#ifndef SERVERCONFIGURATIONMANAGER_H
#define SERVERCONFIGURATIONMANAGER_H

namespace Core::Manager {

class ServerConfigurationManager {
public:
    ServerConfigurationManager();

    int tickRate() const;
    void setTickRate( int tickRate );

    int threadPool() const;
    void setThreadPool( int threadPool );

private:
    int _tickRate;
    int _threadPool;
};

} // namespace Core::Manager

#endif // SERVERCONFIGURATIONMANAGER_H
