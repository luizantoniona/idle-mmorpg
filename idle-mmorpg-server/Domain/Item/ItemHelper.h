#ifndef ITEMHELPER_H
#define ITEMHELPER_H

#include <string>

#include "ItemCategoryType.h"
#include "ItemType.h"

namespace Domain {

class ItemHelper {
public:
    static ItemType stringToType( const std::string& type );
    static std::string typeToString( ItemType type );

    static ItemCategoryType stringToCategoryType( const std::string& type );
    static std::string categoryTypeToString( ItemCategoryType type );
};

} // namespace Domain

#endif // ITEMHELPER_H
