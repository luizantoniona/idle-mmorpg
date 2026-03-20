#ifndef CHARACTEREFFECTSCONTROLLER_H
#define CHARACTEREFFECTSCONTROLLER_H

#include <Domain/Character/Character.h>
#include <Engine/Manager/Item/ItemManager.h>
#include <Engine/Manager/Server/ServerConfigurationManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterEffectsController : public CharacterController {
public:
    explicit CharacterEffectsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                         Domain::Character& character,
                                         Manager::ItemManager& itemManager,
                                         Manager::ServerConfigurationManager& configurationManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    // -- Message methods ---

    // --- EventBus methods ---
    void onApplyEffect( const CharacterEvent& event );

private:
    Domain::CharacterEffects& _characterEffects;
    Manager::ItemManager& _itemManager;
    Manager::ServerConfigurationManager& _configurationManager;

    int _tickRate;
};

} // namespace Engine

#endif // CHARACTEREFFECTSCONTROLLER_H
