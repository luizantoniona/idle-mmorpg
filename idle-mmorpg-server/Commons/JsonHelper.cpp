#include "JsonHelper.h"

#include <fstream>
#include <iostream>

namespace Commons {

Json::Value Commons::JsonHelper::loadJsonFile( const std::string& path ) {
    std::ifstream file( path );
    if ( !file.is_open() ) {
        std::cerr << "JsonHelper::loadJsonFile Could not open file: " << path << std::endl;
        return Json::Value();
    }

    Json::Value jsonData;
    file >> jsonData;
    return jsonData;
}

}
