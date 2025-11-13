#ifndef ITEMMANAGER_H
#define ITEMMANAGER_H

#include <memory>
#include <string>
#include <unordered_map>

#include <Domain/Item/Item.h>

namespace Engine {

class ItemManager {
public:
    ItemManager();

    void initialize( const std::string& itemPath );

    const Domain::Item* itemById( const std::string& idItem ) const;

private:
    std::unordered_map<std::string, std::unique_ptr<Domain::Item> > _items;
};

} // namespace Engine

#endif // ITEMMANAGER_H
