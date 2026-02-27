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

    double baseExperience() const;
    void setBaseExperience( double baseExperience );

    double growthRate() const;
    void setGrowthRate( double growthRate );

private:
    int _tickRate;
    int _threadPool;

    double _baseExperience;
    double _growthRate;
};

} // namespace Manager

#endif // SERVERCONFIGURATIONMANAGER_H
