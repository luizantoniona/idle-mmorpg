#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Model/Item/Item.h>

namespace System::Manager {

class ItemManager {
public:
    ItemManager();

    void initialize( const std::string& itemPath );

    const Model::Item* itemById( const std::string& idItem ) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Model::Item> > _items;
};

} // namespace System::Manager

#endif // ITEMMANAGER_H
