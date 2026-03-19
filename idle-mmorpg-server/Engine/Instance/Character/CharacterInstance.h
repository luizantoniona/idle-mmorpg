#ifndef CHARACTERINSTANCE_H
#define CHARACTERINSTANCE_H

#include <Domain/Character/Character.h>
#include <Engine/Message/MessageReceiverType.h>
#include <Engine/Message/MessageSenderType.h>

#include "Controller/CharacterActionsController.h"
#include "Controller/CharacterCombatController.h"
#include "Controller/CharacterEffectsController.h"
#include "Controller/CharacterItemController.h"
#include "Controller/CharacterProgressionController.h"
#include "Controller/CharacterSkillsController.h"
#include "Controller/CharacterSpellsController.h"
#include "Controller/CharacterStageController.h"
#include "Controller/CharacterVitalsController.h"
#include "EventBus/CharacterEventBus.h"
#include "Message/CharacterMessageSender.h"

namespace Engine {

class CharacterInstance {
public:
    explicit CharacterInstance( std::unique_ptr<Domain::Character> character, drogon::WebSocketConnectionPtr connection );

    std::string sessionId() const;
    void setSessionId( const std::string& sessionId );

    Domain::Character& character();

    void onEnterWorld();
    void onLeaveWorld();

    void onTick();

    void handleMessage( MessageReceiverType type, const Json::Value& payload );
    void sendMessage( MessageSenderType type, const Json::Value& payload );
    void publishEvent( CharacterEventType type, const Json::Value& payload );

private:
    std::string _sessionId;
    std::unique_ptr<Domain::Character> _character;

    CharacterEventBus _eventBus;
    CharacterMessageSender _messageSender;

    std::vector<CharacterController*> _controllers;
    std::unique_ptr<CharacterActionsController> _actionsController;
    std::unique_ptr<CharacterCombatController> _combatController;
    std::unique_ptr<CharacterEffectsController> _effectsController;
    std::unique_ptr<CharacterItemController> _itemController;
    std::unique_ptr<CharacterProgressionController> _progressionController;
    std::unique_ptr<CharacterSkillsController> _skillsController;
    std::unique_ptr<CharacterSpellsController> _spellsController;
    std::unique_ptr<CharacterStageController> _stageController;
    std::unique_ptr<CharacterVitalsController> _vitalsController;
};

} // namespace Engine

#endif // CHARACTERINSTANCE_H
