#ifndef CHARACTERSPELLSCONTROLLER_H
#define CHARACTERSPELLSCONTROLLER_H

#include <Domain/Character/CharacterSpells.h>
#include <Engine/Manager/Spell/SpellManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterSpellsController : public CharacterController {
public:
    explicit CharacterSpellsController( CharacterEventBus& eventBus, CharacterMessageSender& messageSender,
                                        Domain::CharacterSpells& spells,
                                        Manager::SpellManager& spellManager );

    void onEnterWorld() override;
    void onLeaveWorld() override;

    void onTick() override;

private:
    Domain::CharacterSpells& _spells;
    Manager::SpellManager& _spellManager;
};

} // namespace Engine
#endif // CHARACTERSPELLSCONTROLLER_H
