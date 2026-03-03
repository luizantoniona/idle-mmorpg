#ifndef SERVERCONFIGURATIONMANAGER_H
#define SERVERCONFIGURATIONMANAGER_H

#include <string>

namespace Manager {

class ServerConfigurationManager {
public:
    ServerConfigurationManager();

    void initialize( const std::string& configurationPath );

    int tickRate() const;
    int threadPool() const;

    double baseExperience() const;
    double growthRate() const;

private:
    int _tickRate;
    int _threadPool;

    double _baseExperience;
    double _growthRate;
};

} // namespace Manager

#endif // SERVERCONFIGURATIONMANAGER_H
