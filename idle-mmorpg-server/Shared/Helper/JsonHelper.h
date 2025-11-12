#ifndef JSONHELPER_H
#define JSONHELPER_H

#include <string>

#include <json/json.h>

namespace Helper {

class JsonHelper {
public:
    static Json::Value loadJsonFile( const std::string& path );
    static Json::Value parseJsonString( const std::string& content );
};

} // namespace Helper

#endif // JSONHELPER_H
