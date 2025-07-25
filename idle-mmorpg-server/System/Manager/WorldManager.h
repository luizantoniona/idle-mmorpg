#ifndef WORLDMANAGER_H
#define WORLDMANAGER_H

#include <atomic>
#include <memory>
#include <thread>

#include <Model/World/World.h>
#include <System/Instance/WorldInstance.h>

namespace System::Manager {

class WorldManager {
public:
    WorldManager();
    ~WorldManager();

    System::Instance::WorldInstance* worldInstance();

    void initialize( const std::string& mapPath );
    void start();
    void stop();

    bool addCharacter( const std::string& uuid, int idUser, int idCharacter );
    void removeCharacter( const std::string& uuid );

private:
    std::atomic<bool> _running;
    std::thread _thread;
    std::unique_ptr<Model::World> _world;
    std::unique_ptr<System::Instance::WorldInstance> _worldInstance;
};

} // namespace System::Manager

#endif // WORLDMANAGER_H
