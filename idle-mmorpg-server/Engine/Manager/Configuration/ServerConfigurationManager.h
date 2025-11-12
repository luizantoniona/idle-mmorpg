#ifndef SERVERCONFIGURATIONMANAGER_H
#define SERVERCONFIGURATIONMANAGER_H

namespace Engine {

class ServerConfigurationManager {
public:
    ServerConfigurationManager();

    int tickRate() const;
    void setTickRate( int tickRate );

    int threadPool() const;
    void setThreadPool( int threadPool );

    static constexpr double VITAL_SKILL_REGENERATION_MULTIPLIER = 0.25;
    static constexpr double MAGIC_SKILL_HEAL_MULTIPLIER = 0.01;
    static constexpr double MAGIC_SKILL_DAMAGE_MULTIPLIER = 0.01;
    static constexpr double WEAPON_SKILL_DAMAGE_MULTIPLIER = 0.01;

private:
    int _tickRate;
    int _threadPool;
};

} // namespace Engine

#endif // SERVERCONFIGURATIONMANAGER_H
