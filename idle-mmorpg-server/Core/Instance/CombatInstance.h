#ifndef COMBATINSTANCE_H
#define COMBATINSTANCE_H

#include <unordered_map>

//#include <Core/System/CombatSystem.h>
#include <Model/World/Location/Location.h>
#include <Model/Character/Character.h>

namespace Core::Instance {

class CombatInstance {
public:
    explicit CombatInstance( Model::Location* location, const int id, const std::string& structureId = "" );

    Json::Value instanceToJson() const;
    Json::Value combatToJson() const;

    void addCharacter( const std::string& sessionId, Model::Character* character );
    void removeCharacter( const std::string& sessionId );

    bool isFinished() const;

    int id() const;
    std::string structureId() const;
    const std::unordered_map<std::string, Model::Character*>& characters() const;

    void process();

private:
    int _id;
    std::string _structureId;
    Model::Location* _location;
    std::unordered_map<std::string, Model::Character*> _characters;
    std::vector<Model::Creature*> _enemies;
//    Core::System::CombatSystem _combatSystem;
};

}

#endif // COMBATINSTANCE_H
