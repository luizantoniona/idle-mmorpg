#ifndef ITEMHELPER_H
#define ITEMHELPER_H

#include <string>

#include "ItemCategory.h"
#include "ItemType.h"

namespace Domain {

class ItemHelper {
public:
    static ItemType stringToType( const std::string& type );
    static std::string typeToString( ItemType type );

    static ItemCategory stringToCategory( const std::string& category );
    static std::string categoryToString( ItemCategory category );
};

} // namespace Domain

#endif // ITEMHELPER_H
