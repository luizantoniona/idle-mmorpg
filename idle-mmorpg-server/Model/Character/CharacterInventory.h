#ifndef CHARACTERINVENTORY_H
#define CHARACTERINVENTORY_H

#include <map>

#include <Model/Item/Item.h>

namespace Model {

class CharacterInventory {
public:
    CharacterInventory();

//    const std::map<int, int>& items() const;
//    void addItem( const std::string& idItem, int amount );
//    void clear();

//    int amountOfItem( int idItem ) const;

//    void setItemModel( const std::string& idItem, const ItemModel* model );
//    const ItemModel* itemModel( int idItem ) const;

//private:
//    std::map<std::string, int> _itemAmount;
//    std::map<std::string, const ItemModel*> _itemModel;
};

} // namespace Model

#endif // CHARACTERINVENTORY_H
