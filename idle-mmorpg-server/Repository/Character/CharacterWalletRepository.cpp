#include "CharacterWalletRepository.h"

#include <Database/Query.h>

namespace Repository {

CharacterWalletRepository::CharacterWalletRepository() :
    Repository() {}

bool CharacterWalletRepository::createWallet( int idCharacter ) {
    const std::string sql = R"SQL(
        INSERT INTO character_wallet (
            id_character,
            copper,
            silver,
            gold
        ) VALUES (?, 0, 0, 0)
    )SQL";
    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );
    return query.step();
}

bool CharacterWalletRepository::updateCharacterWallet( int idCharacter, const Model::CharacterWallet& wallet ) {
    const std::string sql = R"SQL(
        UPDATE character_wallet SET
            copper = ?,
            silver = ?,
            gold = ?
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );
    query.bindInt( 1, wallet.copper() );
    query.bindInt( 2, wallet.silver() );
    query.bindInt( 3, wallet.gold() );
    query.bindInt( 4, idCharacter );
    return query.step();
}

std::unique_ptr<Model::CharacterWallet> CharacterWalletRepository::findByCharacterId( int idCharacter ) {
    const std::string sql = R"SQL(
        SELECT copper, silver, gold
        FROM character_wallet
        WHERE id_character = ?
    )SQL";
    Database::Query query( _db, sql );
    query.bindInt( 1, idCharacter );

    if ( !query.step() ) {
        return nullptr;
    }

    auto wallet = std::make_unique<Model::CharacterWallet>();
    wallet->setCopper( query.getColumnInt( 0 ) );
    wallet->setSilver( query.getColumnInt( 1 ) );
    wallet->setGold( query.getColumnInt( 2 ) );

    return wallet;
}

} // namespace Repository
