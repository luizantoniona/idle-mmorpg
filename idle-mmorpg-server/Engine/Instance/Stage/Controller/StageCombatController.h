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

    // void createCombat( const std::string& sessionId, CharacterInstance* characterInstance );
    // void enterCombat( const std::string& sessionId, CharacterInstance* characterInstance, const std::string& roomId );
    // void exitCombat( const std::string& sessionId );

private:
    std::vector<std::unique_ptr<CombatInstance>> _combats;
    std::unordered_map<std::string, CombatInstance*> _characterCombatCache;
};

} // namespace Engine

#endif // STAGECOMBATCONTROLLER_H
