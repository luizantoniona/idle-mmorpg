#ifndef CHARACTERSPELLSREPOSITORY_H
#define CHARACTERSPELLSREPOSITORY_H

#include <memory>

#include <Model/Character/CharacterSpells.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterSpellsRepository : public Repository {
public:
    CharacterSpellsRepository();

    bool createSpells( int idCharacter );
    bool updateSpells( int idCharacter, Model::CharacterSpells& characterSpells );

    std::unique_ptr<Model::CharacterSpells> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERSPELLSREPOSITORY_H
