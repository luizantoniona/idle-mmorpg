#ifndef CHARACTERSKILLSREPOSITORY_H
#define CHARACTERSKILLSREPOSITORY_H

#include <memory>

#include <Repository/Repository.h>
#include <Model/Character/CharacterSkills.h>

namespace Repository {

class CharacterSkillsRepository : public Repository {
public:
    CharacterSkillsRepository();

    bool createSkills( int idCharacter );
    bool updateSkills( int idCharacter, Model::CharacterSkills& characterSkills );
    std::unique_ptr<Model::CharacterSkills> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERSKILLSREPOSITORY_H
