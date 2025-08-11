#ifndef COMBATINSTANCE_H
#define COMBATINSTANCE_H

#include <unordered_map>

#include <Core/System/CombatSystem.h>
#include <Model/Character/Character.h>
#include <Model/World/Location/Location.h>

namespace Core::Instance {

class CombatInstance {
public:
    explicit CombatInstance( Model::Location* location, const std::string& id, const std::string& name, const std::string& structureId = "" );

    Json::Value instanceToJson() const;
    Json::Value combatToJson() const;

    void addCharacter( const std::string& sessionId, Model::Character* character );
    void removeCharacter( const std::string& sessionId );

    bool isFinished() const;

    std::string id() const;
    std::string structureId() const;
    const std::unordered_map<std::string, Model::Character*>& characters() const;

    void spawnCreatures();

    void process();

private:
    std::string _id;
    std::string _name;
    std::string _structureId;
    Model::Location* _location;
    std::unordered_map<std::string, Model::Character*> _characters;
    std::vector<std::unique_ptr<Model::Creature>> _creatures;
    Core::System::CombatSystem _combatSystem;
};

} // namespace Core::Instance

#endif // COMBATINSTANCE_H
