#ifndef COMBATINSTANCE_H
#define COMBATINSTANCE_H

#include <unordered_map>

#include <Domain/Stage/Stage.h>
#include <Engine/Instance/Character/CharacterInstance.h>
#include <Engine/Message/MessageReceiverType.h>

#include "Controller/CombatController.h"

namespace Engine {

class CombatInstance {
public:
    explicit CombatInstance( Domain::Stage* stage, const std::string& id, const std::string& name );
    ~CombatInstance();

    std::string id() const;

    const std::unordered_map<std::string, CharacterInstance*>& characters() const;

    bool isFinished() const;

    Json::Value instanceToJson() const;
    Json::Value combatToJson() const;

    void addCharacter( const std::string& sessionId, CharacterInstance* characterInstance );
    void removeCharacter( const std::string& sessionId );

    void shutdown();

    void tick();

    void handleMessage( const std::string& sessionId, MessageReceiverType type, const Json::Value& payload );

private:
    std::string _id;
    std::string _name;
    Domain::Stage* _stage;
    std::unordered_map<std::string, CharacterInstance*> _characters;
    std::vector<std::unique_ptr<Domain::Creature> > _creatures;

    std::unique_ptr<CombatController> _combatController;

    void notifyCombat();

    void spawnCreatures();

    void processCharatersTurn();
    void processCreaturesTurn();

    Domain::Creature* firstAliveCreature();
    CharacterInstance* firstAliveCharacter();
};

} // namespace Engine

#endif // COMBATINSTANCE_H
