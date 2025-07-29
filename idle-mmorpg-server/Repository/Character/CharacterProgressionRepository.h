#ifndef CHARACTERPROGRESSIONREPOSITORY_H
#define CHARACTERPROGRESSIONREPOSITORY_H

#include <memory>

#include <Model/Character/CharacterProgression.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterProgressionRepository : public Repository {
public:
    explicit CharacterProgressionRepository();

    bool createProgression( int idCharacter );
    bool updateProgression( int idCharacter, const Model::CharacterProgression& progression );

    std::unique_ptr<Model::CharacterProgression> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERPROGRESSIONREPOSITORY_H
