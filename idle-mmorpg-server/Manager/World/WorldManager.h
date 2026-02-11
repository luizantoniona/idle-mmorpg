#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <atomic>
#include <memory>
#include <thread>

#include <Domain/World/World.h>
#include <Engine/Instance/World/WorldInstance.h>

namespace Manager {

class WorldManager {
public:
    WorldManager();
    ~WorldManager();

    Engine::WorldInstance* worldInstance();

    void initialize( const std::string& mapPath );
    void stop();

    bool addCharacter( const std::string& sessionId, int idUser, int idCharacter );
    void removeCharacter( const std::string& sessionId );

private:
    std::atomic<bool> _running;
    std::thread _thread;
    std::unique_ptr<Domain::World> _world;
    std::unique_ptr<Engine::WorldInstance> _worldInstance;
};

} // namespace Manager

#endif // WORLDMANAGER_H
