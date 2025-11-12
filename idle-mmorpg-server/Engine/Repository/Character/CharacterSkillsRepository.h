#ifndef CHARACTERSKILLSREPOSITORY_H
#define CHARACTERSKILLSREPOSITORY_H

#include <memory>

#include <Domain/Character/CharacterSkills.h>
#include <Engine/Repository/Repository.h>

namespace Repository {

class CharacterSkillsRepository : public Repository {
public:
    CharacterSkillsRepository();

    bool createSkills( int idCharacter );
    bool updateSkills( int idCharacter, Domain::CharacterSkills& characterSkills );

    std::unique_ptr<Domain::CharacterSkills> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERSKILLSREPOSITORY_H
