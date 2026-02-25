#ifndef CHARACTERINSTANCE_H
#define CHARACTERINSTANCE_H

#include <drogon/WebSocketConnection.h>

#include <Domain/Character/Character.h>
#include <Engine/Message/MessageReceiverType.h>
#include <Engine/Message/MessageSenderType.h>

#include "Controller/CharacterActionsController.h"
#include "Controller/CharacterEffectsController.h"
#include "Controller/CharacterEquipmentController.h"
#include "Controller/CharacterInventoryController.h"
#include "Controller/CharacterProgressionController.h"
#include "Controller/CharacterSkillsController.h"
#include "Controller/CharacterSpellsController.h"
#include "Controller/CharacterVitalsController.h"
#include "Controller/CharacterWalletController.h"

namespace Engine {

class CharacterInstance {
public:
    explicit CharacterInstance( std::unique_ptr<Domain::Character> character, drogon::WebSocketConnectionPtr connection );

    std::string sessionId() const;
    void setSessionId( const std::string& sessionId );

    Domain::Character& character();

    void onEnterWorld();
    void onLeaveWorld();

    void onEnterStage();
    void onLeaveStage();

    void onEnterCombat();
    void onLeaveCombat();

    void onTick();

    void handleMessage( MessageReceiverType type, const Json::Value& payload );
    void sendMessage( MessageSenderType type, const Json::Value& payload );

private:
    std::string _sessionId;
    std::unique_ptr<Domain::Character> _character;

    drogon::WebSocketConnectionPtr _connection;

    std::vector<CharacterController*> _controllers;

    std::unique_ptr<CharacterActionsController> _actionsController;
    std::unique_ptr<CharacterEffectsController> _effectsController;
    std::unique_ptr<CharacterEquipmentController> _equipmentController;
    std::unique_ptr<CharacterInventoryController> _inventoryController;
    std::unique_ptr<CharacterProgressionController> _progressionController;
    std::unique_ptr<CharacterSkillsController> _skillsController;
    std::unique_ptr<CharacterSpellsController> _spellsController;
    std::unique_ptr<CharacterVitalsController> _vitalsController;
    std::unique_ptr<CharacterWalletController> _walletControler;
};

} // namespace Engine

#endif // CHARACTERINSTANCE_H
