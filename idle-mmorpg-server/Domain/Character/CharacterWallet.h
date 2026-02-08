#ifndef CHARACTERWALLET_H
#define CHARACTERWALLET_H

#include <json/json.h>

namespace Domain {

class CharacterWallet {
public:
    CharacterWallet();

    Json::Value toJson();

    int copper() const;
    void setCopper( int copper );

    int silver() const;
    void setSilver( int silver );

    int gold() const;
    void setGold( int gold );

private:
    int _copper;
    int _silver;
    int _gold;
};

} // namespace Domain

#endif // CHARACTERWALLET_H
