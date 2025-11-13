#ifndef CHARACTERQUESTSREPOSITORY_H
#define CHARACTERQUESTSREPOSITORY_H

#include <memory>

#include <Domain/Character/CharacterQuests.h>
#include <Engine/Repository/Repository.h>

namespace Repository {

class CharacterQuestsRepository : public Repository {
public:
    CharacterQuestsRepository();

    bool createQuests( int idCharacter );
    bool updateQuests( int idCharacter, Domain::CharacterQuests& characterQuests );

    std::unique_ptr<Domain::CharacterQuests> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERQUESTSREPOSITORY_H
