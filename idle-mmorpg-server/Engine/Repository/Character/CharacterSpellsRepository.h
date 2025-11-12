#ifndef CHARACTERSPELLSREPOSITORY_H
#define CHARACTERSPELLSREPOSITORY_H

#include <memory>

#include <Domain/Character/CharacterSpells.h>
#include <Engine/Repository/Repository.h>

namespace Repository {

class CharacterSpellsRepository : public Repository {
public:
    CharacterSpellsRepository();

    bool createSpells( int idCharacter );
    bool updateSpells( int idCharacter, Domain::CharacterSpells& characterSpells );

    std::unique_ptr<Domain::CharacterSpells> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERSPELLSREPOSITORY_H
