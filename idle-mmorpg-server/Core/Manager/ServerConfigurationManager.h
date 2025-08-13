#ifndef SERVERCONFIGURATIONMANAGER_H
#define SERVERCONFIGURATIONMANAGER_H

namespace Core::Manager {

class ServerConfigurationManager {
public:
    ServerConfigurationManager();

    int tickRate() const;
    void setTickRate( int tickRate );

private:
    int _tickRate;
};

} // namespace Core::Manager

#endif // SERVERCONFIGURATIONMANAGER_H
