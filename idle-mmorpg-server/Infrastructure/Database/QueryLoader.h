#ifndef QUERYLOADER_H
#define QUERYLOADER_H

#include <string>

namespace Database {

class QueryLoader {
public:
    static std::string loadFromFile( const std::string& path );
    static std::string loadFromString( const std::string& sql );
};

} // namespace Database

#endif // QUERYLOADER_H
