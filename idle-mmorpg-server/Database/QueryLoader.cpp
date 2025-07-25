#include "QueryLoader.h"

#include <fstream>
#include <sstream>

namespace Database {

std::string Database::QueryLoader::loadFromFile( const std::string& path ) {
    std::ifstream file( path );

    if ( !file.is_open() ) {
        throw std::runtime_error( "Failed to open SQL file: " + path );
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

std::string QueryLoader::loadFromString( const std::string& sql ) {
    return sql;
}

} // namespace Database
