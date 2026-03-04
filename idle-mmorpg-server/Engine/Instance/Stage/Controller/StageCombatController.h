#ifndef STAGECOMBATCONTROLLER_H
#define STAGECOMBATCONTROLLER_H

#include <Domain/Stage/Stage.h>
#include <Engine/Instance/Combat/CombatInstance.h>

#include "StageController.h"

namespace Engine {

class StageCombatController : public StageController {
public:
    explicit StageCombatController( Domain::Stage* stage );

    void onCharacterEnter( CharacterInstance* characterInstance ) override;
    void onCharacterExit( const std::string& sessionId ) override;

    void onTick() override;

    void handleMessage( CharacterInstance* characterInstance, MessageReceiverType type, const Json::Value& payload ) override;

private:
    std::unordered_map<std::string, std::unique_ptr<CombatInstance>> _combats;
    std::unordered_map<std::string, CharacterInstance*> _characters;
    std::unordered_map<std::string, CombatInstance*> _characterToCombatCache;

    void notifyCombatRooms();

    void createCombat( CharacterInstance* characterInstance );
    void enterCombat( CharacterInstance* characterInstance, const std::string& roomId );
    void exitCombat( CharacterInstance* characterInstance );
};

} // namespace Engine

#endif // STAGECOMBATCONTROLLER_H
