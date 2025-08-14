#ifndef CHARACTERQUESTSREPOSITORY_H
#define CHARACTERQUESTSREPOSITORY_H

#include <memory>

#include <Model/Character/CharacterQuests.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterQuestsRepository : public Repository {
public:
    CharacterQuestsRepository();

    bool createQuests( int idCharacter );
    bool updateQuests( int idCharacter, Model::CharacterQuests& characterQuests );

    std::unique_ptr<Model::CharacterQuests> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERQUESTSREPOSITORY_H
