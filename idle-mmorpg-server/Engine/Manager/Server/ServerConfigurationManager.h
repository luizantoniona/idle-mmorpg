#ifndef SERVERCONFIGURATIONMANAGER_H
#define SERVERCONFIGURATIONMANAGER_H

#include <string>

namespace Manager {

struct VitalRate {
    int health;
    int mana;
    int stamina;
};

class ServerConfigurationManager {
public:
    ServerConfigurationManager();

    void initialize( const std::string& configurationPath );

    const VitalRate& vitalsRate() const;

    // TODO: Create separated structs for general configurations
    int tickRate() const;
    int threadPool() const;

    double baseExperience() const;
    double growthRate() const;

private:
    VitalRate _vitalsRate;

    // TODO: Create separated structs for general configurations
    int _tickRate;
    int _threadPool;

    double _baseExperience;
    double _growthRate;
};

} // namespace Manager

#endif // SERVERCONFIGURATIONMANAGER_H
