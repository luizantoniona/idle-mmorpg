#ifndef CHARACTERPROGRESSIONCONTROLLER_H
#define CHARACTERPROGRESSIONCONTROLLER_H

#include <Domain/Character/Character.h>
#include <Engine/Manager/Server/ServerConfigurationManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterProgressionController : public CharacterController {
public:
    explicit CharacterProgressionController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                             Domain::Character& character,
                                             Manager::ServerConfigurationManager& configurationManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    // -- Message methods ---

    // --- EventBus methods ---
    void onProgressionExperienceGained( const CharacterEvent& event );

    void applyLevelUp();

private:
    Domain::CharacterProgression& _characterProgression;
    Manager::ServerConfigurationManager& _configurationManager;
};

} // namespace Engine

#endif // CHARACTERPROGRESSIONCONTROLLER_H
