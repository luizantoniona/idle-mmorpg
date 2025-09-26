#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <atomic>
#include <memory>
#include <thread>

#include <Core/Instance/WorldInstance.h>
#include <Model/World/World.h>

namespace Core::Manager {

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
    std::unique_ptr<Model::World> _world;
    std::unique_ptr<Core::Instance::WorldInstance> _worldInstance;
};

} // namespace Core::Manager

#endif // WORLDMANAGER_H
