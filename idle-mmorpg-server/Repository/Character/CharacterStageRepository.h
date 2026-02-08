#ifndef CHARACTERSTAGEREPOSITORY_H
#define CHARACTERSTAGEREPOSITORY_H

#include <memory>

#include <Domain/Character/CharacterStage.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterStageRepository : public Repository {
public:
    CharacterStageRepository();

    bool createStage( int idCharacter );
    bool updateStage( int idCharacter, const Domain::CharacterStage& stage );

    std::unique_ptr<Domain::CharacterStage> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERSTAGEREPOSITORY_H
