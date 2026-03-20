#ifndef CHARACTERVITALSCONTROLLER_H
#define CHARACTERVITALSCONTROLLER_H

#include <Domain/Character/Character.h>
#include <Engine/Manager/Server/ServerConfigurationManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterVitalsController : public CharacterController {
public:
    explicit CharacterVitalsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                        Domain::Character& character,
                                        Manager::ServerConfigurationManager& configurationManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    // -- Message methods ---

    // --- EventBus methods ---
    void onVitalMaxHealthGained( const CharacterEvent& event );
    void onVitalMaxManaGained( const CharacterEvent& event );
    void onVitalMaxStaminaGained( const CharacterEvent& event );
    void onVitalHealthChanged( const CharacterEvent& event );
    void onVitalManaChanged( const CharacterEvent& event );
    void onVitalStaminaChanged( const CharacterEvent& event );

private:
    Domain::Character& _character;
    Domain::CharacterVitals& _characterVitals;
    Manager::ServerConfigurationManager& _configurationManager;
};

} // namespace Engine

#endif // CHARACTERVITALSCONTROLLER_H
