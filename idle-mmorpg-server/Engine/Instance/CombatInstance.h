#ifndef COMBATINSTANCE_H
#define COMBATINSTANCE_H

#include <unordered_map>

#include <Domain/Character/Character.h>
#include <Domain/Stage/Stage.h>

namespace Engine {

class CombatInstance {
public:
    explicit CombatInstance( Domain::Stage* stage, const std::string& id, const std::string& name );

    Json::Value instanceToJson() const;
    Json::Value combatToJson() const;

    void addCharacter( const std::string& sessionId, Domain::Character* character );
    void removeCharacter( const std::string& sessionId );

    bool isFinished() const;

    std::string id() const;

    const std::unordered_map<std::string, Domain::Character*>& characters() const;

    void spawnCreatures();

    void process();

    void handleCharacterAttackSpell( const std::string& sessionId, Domain::Character* character, const std::string& spellId );

private:
    std::string _id;
    std::string _name;
    Domain::Stage* _stage;
    std::unordered_map<std::string, Domain::Character*> _characters;
    std::vector<std::unique_ptr<Domain::Creature> > _creatures;
};

} // namespace Engine

#endif // COMBATINSTANCE_H
