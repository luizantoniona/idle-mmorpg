#ifndef CHARACTERITEM_H
#define CHARACTERITEM_H

#include <string>

#include <Model/Item/Item.h>

namespace Model {

class CharacterItem {
public:
    CharacterItem();

    std::string id() const;
    void setId( const std::string& id );

    int amount() const;
    void setAmount( int amount );

    Item* item() const;
    void setItem( Item* item );

private:
    std::string _id;
    int _amount;
    Item* _item;
};

} // namespace Model

#endif // CHARACTERITEM_H
