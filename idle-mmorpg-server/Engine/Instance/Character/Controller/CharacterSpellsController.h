#ifndef CHARACTERSPELLSCONTROLLER_H
#define CHARACTERSPELLSCONTROLLER_H

#include <Domain/Character/CharacterSpells.h>
#include <Manager/Spell/SpellManager.h>

#include "CharacterController.h"

namespace Engine {

class CharacterSpellsController : public CharacterController {
public:
    explicit CharacterSpellsController( Domain::CharacterSpells& spells, Manager::SpellManager& spellManager );

    void onEnterWorld() override;
    void onTickWorld() override;
    void onExitWorld() override;

private:
    Domain::CharacterSpells& _spells;
    Manager::SpellManager& _spellManager;
};

} // namespace Engine
#endif // CHARACTERSPELLSCONTROLLER_H
