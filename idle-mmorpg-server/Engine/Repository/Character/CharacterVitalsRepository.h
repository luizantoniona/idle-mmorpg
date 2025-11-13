#ifndef CHARACTERVITALSREPOSITORY_H
#define CHARACTERVITALSREPOSITORY_H

#include <memory>

#include <Domain/Character/CharacterVitals.h>
#include <Engine/Repository/Repository.h>

namespace Repository {

class CharacterVitalsRepository : public Repository {
public:
    explicit CharacterVitalsRepository();

    bool createVitals( int idCharacter );
    bool updateVitals( int idCharacter, const Domain::CharacterVitals& vitals );

    std::unique_ptr<Domain::CharacterVitals> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERVITALSREPOSITORY_H
