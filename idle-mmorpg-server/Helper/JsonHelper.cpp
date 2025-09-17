#include "JsonHelper.h"

#include <fstream>
#include <iostream>

namespace Helper {

Json::Value JsonHelper::loadJsonFile( const std::string& path ) {
    std::ifstream file( path );
    if ( !file.is_open() ) {
        std::cerr << "JsonHelper::loadJsonFile Could not open file: " << path << std::endl;
        return Json::Value();
    }

    Json::Value jsonData;
    file >> jsonData;
    return jsonData;
}

Json::Value JsonHelper::parseJsonString( const std::string& content ) {
    Json::Value jsonData;
    Json::CharReaderBuilder builder;
    std::string errs;

    std::istringstream s( content );
    if ( !Json::parseFromStream( builder, s, &jsonData, &errs ) ) {
        std::cerr << "JsonHelper::parseJsonString Error parsing JSON: " << errs << std::endl;
        return Json::Value();
    }

    return jsonData;
}

} // namespace Helper
