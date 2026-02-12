#ifndef STAGECOMBATCONTROLLER_H
#define STAGECOMBATCONTROLLER_H

#include <Domain/Stage/Stage.h>
#include <Engine/Instance/Combat/CombatInstance.h>

namespace Engine {

class StageCombatController {
public:
    explicit StageCombatController( Domain::Stage* stage );

    void onCharacterEnter();
    void onCharacterExit();

    void tick();

    // void createCombat( const std::string& sessionId, CharacterInstance* characterInstance );
    // void enterCombat( const std::string& sessionId, CharacterInstance* characterInstance, const std::string& roomId );
    // void exitCombat( const std::string& sessionId );

private:
    Domain::Stage* _stage;
    std::vector<std::unique_ptr<CombatInstance>> _combats;
    std::unordered_map<std::string, CombatInstance*> _characterCombatCache;
};

} // namespace Engine

#endif // STAGECOMBATCONTROLLER_H
