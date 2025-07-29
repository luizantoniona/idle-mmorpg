#ifndef CHARACTERVITALSREPOSITORY_H
#define CHARACTERVITALSREPOSITORY_H

#include <memory>

#include <Model/Character/CharacterVitals.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterVitalsRepository : public Repository {
public:
    explicit CharacterVitalsRepository();

    bool createVitals( int idCharacter );
    bool updateVitals( int idCharacter, const Model::CharacterVitals& vitals );

    std::unique_ptr<Model::CharacterVitals> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERVITALSREPOSITORY_H
