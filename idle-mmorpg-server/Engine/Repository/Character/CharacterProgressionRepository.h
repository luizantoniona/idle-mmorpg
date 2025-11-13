#ifndef CHARACTERPROGRESSIONREPOSITORY_H
#define CHARACTERPROGRESSIONREPOSITORY_H

#include <memory>

#include <Domain/Character/CharacterProgression.h>
#include <Engine/Repository/Repository.h>

namespace Repository {

class CharacterProgressionRepository : public Repository {
public:
    explicit CharacterProgressionRepository();

    bool createProgression( int idCharacter );
    bool updateProgression( int idCharacter, const Domain::CharacterProgression& progression );

    std::unique_ptr<Domain::CharacterProgression> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERPROGRESSIONREPOSITORY_H
