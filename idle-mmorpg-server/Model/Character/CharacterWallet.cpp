#include "CharacterWallet.h"

namespace Model {

CharacterWallet::CharacterWallet() :
    _copper( 0 ),
    _silver( 0 ),
    _gold( 0 ) {}

Json::Value CharacterWallet::toJson() {
    Json::Value root;

    root[ "copper" ] = copper();
    root[ "silver" ] = silver();
    root[ "gold" ] = gold();

    return root;
}

int CharacterWallet::copper() const {
    return _copper;
}

void CharacterWallet::setCopper( int copper ) {
    _copper = copper;
}

int CharacterWallet::silver() const {
    return _silver;
}

void CharacterWallet::setSilver( int silver ) {
    _silver = silver;
}

int CharacterWallet::gold() const {
    return _gold;
}

void CharacterWallet::setGold( int gold ) {
    _gold = gold;
}

} // namespace Model
