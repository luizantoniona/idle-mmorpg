#include "CharacterSkillsRepository.h"

#include <Domain/Skill/SkillHelper.h>
#include <Infrastructure/Database/Query.h>

namespace Repository {

CharacterSkillsRepository::CharacterSkillsRepository() :
    Repository() {}

bool CharacterSkillsRepository::createSkills( int idCharacter ) {
    return true;
}

bool CharacterSkillsRepository::updateSkills( int idCharacter, Domain::CharacterSkills& characterSkills ) {
    const std::string upsertSql = R"SQL(
        INSERT INTO character_skills (id_character, id_skill, experience, level)
        VALUES (?, ?, ?, ?)
        ON CONFLICT(id_character, id_skill) DO UPDATE SET
            experience = excluded.experience,
            level = excluded.level
    )SQL";

    for ( auto& [type, skill] : characterSkills.skills() ) {

        Database::Query query( _db, upsertSql );
        query.bindInt( 1, idCharacter );
        query.bindText( 2, Domain::SkillHelper::typeToString( type ) );
        query.bindInt( 3, skill.experience() );
        query.bindInt( 4, skill.level() );

        if ( !query.exec() ) {
            return false;
        }
    }

    return true;
}

std::unique_ptr<Domain::CharacterSkills> CharacterSkillsRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT id_skill, experience, level FROM character_skills WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    auto skills = std::make_unique<Domain::CharacterSkills>();

    while ( query.step() ) {
        Domain::CharacterSkill characterSkill;
        characterSkill.setType( Domain::SkillHelper::stringToType( query.getColumnText( 0 ) ) );
        characterSkill.setExperience( query.getColumnInt( 1 ) );
        characterSkill.setLevel( query.getColumnInt( 2 ) );

        skills->addSkill( characterSkill );
    }

    return skills;
}

} // namespace Repository
