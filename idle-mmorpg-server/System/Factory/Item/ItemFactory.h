#ifndef ITEMFACTORY_H
#define ITEMFACTORY_H

#include <memory>
#include <unordered_map>

#include <Model/Item/Item.h>

namespace System::Factory {

class ItemFactory {
public:
    static std::unordered_map<std::string, std::unique_ptr<Model::Item> > createItems( const std::string& itemsPath );

private:
    static std::unique_ptr<Model::Item> createItem( const std::string& itemPath );
};

} // namespace System::Factory

#endif // ITEMFACTORY_H
