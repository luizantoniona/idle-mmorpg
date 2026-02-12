#ifndef CHARACTERSPELLSCONTROLLER_H
#define CHARACTERSPELLSCONTROLLER_H

#include <Domain/Character/CharacterSpells.h>
#include <Manager/Spell/SpellManager.h>

namespace Engine {

class CharacterSpellsController {
public:
    explicit CharacterSpellsController( Domain::CharacterSpells& spells, Manager::SpellManager& spellManager );

    void onEnterWorld();
    void onExitWorld();

    void tick();

private:
    Domain::CharacterSpells& _spells;
    Manager::SpellManager& _spellManager;
};

} // namespace Engine
#endif // CHARACTERSPELLSCONTROLLER_H
