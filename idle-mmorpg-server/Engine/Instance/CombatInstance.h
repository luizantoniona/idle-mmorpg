#ifndef COMBATINSTANCE_H
#define COMBATINSTANCE_H

#include <unordered_map>

#include <Domain/Character/Character.h>
#include <Domain/World/Location/Location.h>
#include <Engine/System/CombatSystem.h>

namespace Engine {

class CombatInstance {
public:
    explicit CombatInstance( Domain::Location* location, const std::string& id, const std::string& name, const std::string& structureId = "" );

    Json::Value instanceToJson() const;
    Json::Value combatToJson() const;

    void addCharacter( const std::string& sessionId, Domain::Character* character );
    void removeCharacter( const std::string& sessionId );

    void handleCharacterAttackSpell( const std::string& sessionId, Domain::Character* character, const std::string& spellId );

    bool isFinished() const;

    std::string id() const;
    std::string structureId() const;
    const std::unordered_map<std::string, Domain::Character*>& characters() const;

    void spawnCreatures();

    void process();

private:
    std::string _id;
    std::string _name;
    std::string _structureId;
    Domain::Location* _location;
    std::unordered_map<std::string, Domain::Character*> _characters;
    std::vector<std::unique_ptr<Domain::Creature> > _creatures;
    Core::System::CombatSystem _combatSystem;
};

} // namespace Engine

#endif // COMBATINSTANCE_H
