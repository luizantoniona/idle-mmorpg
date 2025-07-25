#ifndef CHARACTERWALLETREPOSITORY_H
#define CHARACTERWALLETREPOSITORY_H

#include <memory>

#include <Model/Character/CharacterWallet.h>
#include <Repository/Repository.h>

namespace Repository {

class CharacterWalletRepository : public Repository {
public:
    explicit CharacterWalletRepository();

    bool createWallet( int idCharacter );

    bool updateCharacterWallet( int idCharacter, const Model::CharacterWallet& inventory );

    std::unique_ptr<Model::CharacterWallet> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERWALLETREPOSITORY_H
