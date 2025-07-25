#include "CharacterSkillsRepository.h"

#include <Database/Query.h>

namespace Repository {

CharacterSkillsRepository::CharacterSkillsRepository() :
    Repository() {}

bool CharacterSkillsRepository::createSkills( int idCharacter ) {
    return true;
}

bool CharacterSkillsRepository::updateSkills( int idCharacter, const Model::CharacterSkills& skills ) {
    const std::string deleteSql = R"SQL(
        DELETE FROM character_skills WHERE id_character = ?
    )SQL";

    Database::Query deleteQuery( _db, deleteSql );
    deleteQuery.bindInt( 1, idCharacter );

    if ( !deleteQuery.step() ) {
        return false;
    }

    const std::string insertSql = R"SQL(
        INSERT INTO character_skills (id_character, id_skill, experience, level) VALUES (?, ?, ?, ?)
    )SQL";

    for ( const auto& [ skillId, skill ] : skills.skills() ) {
        Database::Query insertQuery( _db, insertSql );
        insertQuery.bindInt( 1, idCharacter );
        insertQuery.bindText( 2, skill.id() );
        insertQuery.bindInt( 3, skill.experience() );
        insertQuery.bindInt( 4, skill.level() );

        if ( !insertQuery.step() ) {
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

        Model::CharacterSkill characterSkill;
        characterSkill.setId( skillId );
        characterSkill.setExperience( experience );
        characterSkill.setLevel( level );
        skills->addSkill( characterSkill );
    }

    return skills;
}

} // namespace Repository
