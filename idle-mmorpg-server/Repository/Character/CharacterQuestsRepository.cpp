#include "CharacterQuestsRepository.h"

#include <Commons/Singleton.h>
#include <Core/Manager/QuestManager.h>
#include <Database/Query.h>

namespace Repository {

CharacterQuestsRepository::CharacterQuestsRepository() :
    Repository() {
}

bool CharacterQuestsRepository::createQuests( int idCharacter ) {
    return true;
}

bool CharacterQuestsRepository::updateQuests( int idCharacter, Model::CharacterQuests& characterQuests ) {
    const std::string upsertSql = R"SQL(
        INSERT INTO character_quests (id_character, id_quest, type, objective_id, current_amount, objective_amount, finished, claimed)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?)
        ON CONFLICT(id_character, id_quest) DO UPDATE SET
            current_amount = excluded.current_amount,
            objective_amount = excluded.objective_amount,
            finished = excluded.finished,
            claimed = excluded.claimed
    )SQL";

    for ( auto& quest : characterQuests.proceeding() ) {
        Database::Query upsertQuery( _db, upsertSql );
        upsertQuery.bindInt( 1, idCharacter );
        upsertQuery.bindText( 2, quest.id() );
        upsertQuery.bindText( 3, quest.type() );
        upsertQuery.bindText( 4, quest.objectiveId() );
        upsertQuery.bindInt( 5, quest.currentAmount() );
        upsertQuery.bindInt( 6, quest.objectiveAmount() );
        upsertQuery.bindInt( 7, quest.finished() ? 1 : 0 );
        upsertQuery.bindInt( 8, 0 );

        if ( !upsertQuery.exec() ) {
            return false;
        }
    }

    for ( auto& quest : characterQuests.finished() ) {
        Database::Query upsertQuery( _db, upsertSql );
        upsertQuery.bindInt( 1, idCharacter );
        upsertQuery.bindText( 2, quest.id() );
        upsertQuery.bindText( 3, quest.type() );
        upsertQuery.bindText( 4, quest.objectiveId() );
        upsertQuery.bindInt( 5, quest.currentAmount() );
        upsertQuery.bindInt( 6, quest.objectiveAmount() );
        upsertQuery.bindInt( 7, 1 );
        upsertQuery.bindInt( 8, quest.finished() ? 1 : 0 );

        if ( !upsertQuery.exec() ) {
            return false;
        }
    }

    return true;
}

std::unique_ptr<Model::CharacterQuests> CharacterQuestsRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT id_quest, type, objective_id, current_amount, objective_amount, finished, claimed
        FROM character_quests
        WHERE id_character = ?
    )SQL";

    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    auto characterQuests = std::make_unique<Model::CharacterQuests>();

    while ( query.step() ) {
        Model::CharacterQuest quest;
        quest.setId( query.getColumnText( 0 ) );
        quest.setType( query.getColumnText( 1 ) );
        quest.setObjectiveId( query.getColumnText( 2 ) );
        quest.setCurrentAmount( query.getColumnInt( 3 ) );
        quest.setObjectiveAmount( query.getColumnInt( 4 ) );
        quest.setFinished( query.getColumnInt( 5 ) != 0 );
        quest.setQuest( Commons::Singleton<Core::Manager::QuestManager>::instance().questById( quest.id() ) );

        bool claimed = query.getColumnInt( 6 ) != 0;
        if ( quest.finished() ) {
            if ( claimed ) {
                characterQuests->addFinished( quest );
            } else {
                characterQuests->addProceeding( quest );
            }
        } else {
            characterQuests->addProceeding( quest );
        }
    }

    return characterQuests;
}

} // namespace Repository
