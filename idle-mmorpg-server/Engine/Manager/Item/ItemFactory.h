#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <memory>
#include <unordered_map>

#include <Domain/Item/Item.h>

namespace Engine {

class ItemFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Domain::Item> > createItems( const std::string& itemsPath );

private:
    static std::unique_ptr<Domain::Item> createItem( const std::string& itemPath );
};

} // namespace Engine

#endif // ITEMFACTORY_H
