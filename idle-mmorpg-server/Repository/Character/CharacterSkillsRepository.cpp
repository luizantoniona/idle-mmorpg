#include "CharacterSkillsRepository.h"

#include <Commons/Singleton.h>
#include <Core/Manager/SkillManager.h>
#include <Database/Query.h>

namespace Repository {

CharacterSkillsRepository::CharacterSkillsRepository() :
    Repository() {}

bool CharacterSkillsRepository::createSkills( int idCharacter ) {
    return true;
}

bool CharacterSkillsRepository::updateSkills( int idCharacter, Model::CharacterSkills& characterSkills ) {
    const std::string upsertSql = R"SQL(
        INSERT INTO character_skills (id_character, id_skill, experience, level)
        VALUES (?, ?, ?, ?)
        ON CONFLICT(id_character, id_skill) DO UPDATE SET
            experience = excluded.experience,
            level = excluded.level
    )SQL";

    for ( auto& skill : characterSkills.skills() ) {

        Database::Query upsertQuery( _db, upsertSql );
        upsertQuery.bindInt( 1, idCharacter );
        upsertQuery.bindText( 2, skill.id() );
        upsertQuery.bindInt( 3, skill.experience() );
        upsertQuery.bindInt( 4, skill.level() );

        if ( !upsertQuery.exec() ) {
            return false;
        }
    }

    return true;
}

std::unique_ptr<Model::CharacterSkills> CharacterSkillsRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT id_skill, experience, level FROM character_skills WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    auto skills = std::make_unique<Model::CharacterSkills>();

    while ( query.step() ) {
        std::string skillId = query.getColumnText( 0 );
        int experience = query.getColumnInt( 1 );
        int level = query.getColumnInt( 2 );

        auto skill = Commons::Singleton<Core::Manager::SkillManager>::instance().skill( skillId );
        if ( skill ) {
            Model::CharacterSkill characterSkill;
            characterSkill.setId( skillId );
            characterSkill.setExperience( experience );
            characterSkill.setLevel( level );
            characterSkill.setSkill( skill );
            skills->addSkill( characterSkill );
        }
    }

    return skills;
}

} // namespace Repository
