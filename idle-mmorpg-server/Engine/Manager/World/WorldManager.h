#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <atomic>
#include <memory>
#include <thread>

#include <Engine/Instance/WorldInstance.h>
#include <Domain/World/World.h>

namespace Engine {

class WorldManager {
public:
    WorldManager();
    ~WorldManager();

    Core::Instance::WorldInstance* worldInstance();

    void initialize( const std::string& mapPath );
    void start();
    void stop();

    bool addCharacter( const std::string& sessionId, int idUser, int idCharacter );
    void removeCharacter( const std::string& uuid );

private:
    std::atomic<bool> _running;
    std::thread _thread;
    std::unique_ptr<Domain::World> _world;
    std::unique_ptr<Engine::WorldInstance> _worldInstance;
};

} // namespace Engine

#endif // WORLDMANAGER_H
