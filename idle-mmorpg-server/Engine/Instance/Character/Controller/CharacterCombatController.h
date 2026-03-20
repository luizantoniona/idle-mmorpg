#ifndef CHARACTERCOMBATCONTROLLER_H
#define CHARACTERCOMBATCONTROLLER_H

#include <Domain/Character/Character.h>
#include <Engine/Manager/Server/ServerConfigurationManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterCombatController : public CharacterController {
public:
    explicit CharacterCombatController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                        Domain::Character& character,
                                        Manager::ServerConfigurationManager& configurationManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

    void handleMessage( MessageReceiverType type, const Json::Value& payload ) override;

private:
    // -- Message methods ---

    // --- EventBus methods ---
    void onCombatEnter( const CharacterEvent& event );
    void onCombatExit( const CharacterEvent& event );
    void onItemEquipped( const CharacterEvent& event );
    void onSkillLeveledUp( const CharacterEvent& event );

    void recomputeCombatAttributes();

private:
    Domain::Character& _character;
    Domain::CharacterCombat& _characterCombat;
    Manager::ServerConfigurationManager& _configurationManager;
};

} // namespace Engine

#endif // CHARACTERCOMBATCONTROLLER_H
