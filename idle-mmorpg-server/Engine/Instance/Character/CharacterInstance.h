#ifndef CHARACTERINSTANCE_H
#define CHARACTERINSTANCE_H

#include <Domain/Character/Character.h>
#include <Engine/Message/MessageReceiverType.h>

#include "Controller/CharacterActionsController.h"
#include "Controller/CharacterEffectsController.h"
#include "Controller/CharacterEquipmentController.h"
#include "Controller/CharacterInventoryController.h"
#include "Controller/CharacterSkillsController.h"
#include "Controller/CharacterSpellsController.h"
#include "Controller/CharacterVitalsController.h"

namespace Engine {

class CharacterInstance {
public:
    explicit CharacterInstance( std::unique_ptr<Domain::Character> );

    std::string sessionId() const;
    void setSessionId( const std::string& sessionId );

    Domain::Character& character();

    void onEnterWorld();
    void onLeaveWorld();

    void tick();

    void handleMessage( const std::string& sessionId, MessageReceiverType type, const Json::Value& payload );

private:
    std::string _sessionId;
    std::unique_ptr<Domain::Character> _character;

    std::unique_ptr<CharacterActionsController> _actionsController;
    std::unique_ptr<CharacterEffectsController> _effectsController;
    std::unique_ptr<CharacterEquipmentController> _equipmentController;
    std::unique_ptr<CharacterInventoryController> _inventoryController;
    // Progression
    std::unique_ptr<CharacterSkillsController> _skillsController;
    std::unique_ptr<CharacterSpellsController> _spellsController;
    std::unique_ptr<CharacterVitalsController> _vitalsController;
    // Wallet
};

} // namespace Engine

#endif // CHARACTERINSTANCE_H
