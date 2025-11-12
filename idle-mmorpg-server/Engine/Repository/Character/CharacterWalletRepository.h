#ifndef CHARACTERWALLETREPOSITORY_H
#define CHARACTERWALLETREPOSITORY_H

#include <memory>

#include <Domain/Character/CharacterWallet.h>
#include <Engine/Repository/Repository.h>

namespace Repository {

class CharacterWalletRepository : public Repository {
public:
    explicit CharacterWalletRepository();

    bool createWallet( int idCharacter );
    bool updateWallet( int idCharacter, const Domain::CharacterWallet& wallet );

    std::unique_ptr<Domain::CharacterWallet> findByCharacterId( int idCharacter );
};

} // namespace Repository

#endif // CHARACTERWALLETREPOSITORY_H
